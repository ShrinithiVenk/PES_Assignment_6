#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "UI.h"

#define OVERSAMPLE_RATE 16

/*******************************************************
 * UART Configuration
 ******************************************************/
#define	BAUD_RATE 38400
#define DATA_SIZE 8
#define PARITY 0
#define	STOP_BITS 2


void transmit(const void* str, size_t count);
size_t receive(void* str, size_t count);
void Init_UART0(uint32_t baud_rate);
void accumulate(void);

#endif /* UART_H_ */
