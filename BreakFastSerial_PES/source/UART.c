#include "UART.h"
#include <stdint.h>
#include "MKL25Z4.h"
#include "UI.h"
#include "sysclock.h"
#include "cbfifo.h"

CBfifo_struct RxQ, TxQ;

/**
 * @Function: 	 Initializes the serial communication
 * @Parameters:  baud_rate
 * @Returns   :  Null
 */
void UART0_Init(uint32_t baud_rate)
{
	uint16_t setbaudrate;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;


	// Set UART clock to 24 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	setbaudrate = (uint16_t)((SYSCLOCK_FREQUENCY)/(BAUD_RATE * OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(setbaudrate>>8);
	UART0->BDL = UART0_BDL_SBR(setbaudrate);
	UART0->C4 |= UART0_C4_OSR(OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select two stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(PARITY);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
									| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);


	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	cbfifo_Init(&RxQ);
	cbfifo_Init(&TxQ);

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	if (temp) {}
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}

/**
 * @Function: 	 Interrupt handler function that priorities the particular interrupts transmitted and received through UART
 * @Parameters:  Null
 * @Returns   :  Null
 */
void UART0_IRQHandler(void)
{
	uint8_t byte;
	size_t return_bytes=0;

	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
			UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		byte = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		byte = UART0->D;
		return_bytes = cbfifo_enqueue(&RxQ, &byte, 1);
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character
		return_bytes = cbfifo_dequeue(&TxQ, &byte, 1);
		if (return_bytes==1) {
			UART0->D = byte;
		} else {
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

/**
 * @Function: 	 Transmit function that allows to write to the buffer
 * @Parameters:  buffer, count, handle
 * @Returns   :  Null
 */
int __sys_write(int handle, char* buffer, int count){
	if(buffer == NULL){
		//Return error if null character is passed
		return -1;
	}

	while(cbfifo_full(&TxQ)){
		;	//Wait if transmitter buffer is full
	}

	if(cbfifo_enqueue(&TxQ, buffer, count) != count){
		//Error if enqueued further
		return -1;
	}
	if(!(UART0->C2 & UART0_C2_TIE_MASK)){
		UART0->C2 |= UART0_C2_TIE(1);
	}
	return 0;
}

/**
 * @Function: 	 Receive function that allows to receive output from the buffer
 * @Parameters:  Null
 * @Returns   :  Received character
 */
int __sys_readc(void){
	char chatr;
	if(cbfifo_dequeue(&RxQ, &chatr, 1) != 1){
		return -1;
	}
	if((chatr == '\r') || (chatr == '\r')){
		chatr = '\r';
		printf("%c", chatr);
		chatr = '\n';
		printf("%c", chatr);
	}
	else{
		printf("%c", chatr);
	}
	return chatr;
}


