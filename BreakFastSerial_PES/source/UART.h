#ifndef UART_H_
#define UART_H_
#include <stdio.h>
#include "cbfifo.h"

extern CBfifo_struct RxQ, TxQ;

 // UART Configuration

#define OVERSAMPLE_RATE 16
#define	BAUD_RATE 38400
#define DATA_SIZE 8
#define PARITY 0
#define	STOP_BITS 2

/**
 * @Function: 	 Initializes the serial communication
 * @Parameters:  baud_rate
 * @Returns   :  Null
 */
void UART0_Init(uint32_t baud_rate);

/**
 * @Function: 	 Transmit function that allows to write to the buffer
 * @Parameters:  buffer, count, handle
 * @Returns   :  Null
 */
int __sys_write(int handle, char* buffer, int count);

/**
 * @Function: 	 Receive function that allows to receive output from the buffer
 * @Parameters:  Null
 * @Returns   :  Received character
 */
int __sys_readc(void);


#endif /* UART_H_ */
