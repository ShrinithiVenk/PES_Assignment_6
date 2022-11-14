#ifndef CBFIFO_H
#define CBFIFO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <MKL25Z4.h>

#define BUFFER_SIZE 256

/**
 * Structure with states of the circular buffer
 */
typedef struct
{
  char buffer_array[BUFFER_SIZE];
  uint8_t read, write;
  size_t max_len;
  size_t length;
  bool full;
  bool empty;

}CBfifo_struct;

/*
 * @Function	Initializes the structure for cbfifo.
 * @Param		Null
 * @Returns		Null
 */
void cbfifo_Init(CBfifo_struct *queue);

/*
 * @Function	Enqueues data onto the FIFO, up to the limit of the available FIFO capacity.
 * @Param		str, nbytes
 * @Returns		The number of bytes enqueued, which will be between 0 and nbyte.
 */
size_t cbfifo_enqueue(CBfifo_struct *queue, const void *str, size_t nbytes);

/*
 * @Function	Dequeues up to nbytes of data from the FIFO.
 * @Param		str, nbtes
 * @Returns		The number of bytes removed, which will be between 0 and nbyte.
 */
size_t cbfifo_dequeue(CBfifo_struct *queue, void *str, size_t nbytes);

/*
 * @Function	Returns the length of the fifo
 * @Param		null
 * @Returns		returns the size of the fifo in bytes
 */
size_t cbfifo_length(CBfifo_struct *queue);

/*
 * @Function	Returns the current capacity of the fifo
 * @Param		null
 * @Returns		the current capacity of the fifo in bytes
 */
size_t cbfifo_capacity();

/*
 * @Function	checks for buffer if full
 * @Param		null
 * @Returns		returns if buffer full
 */
bool cbfifo_full(CBfifo_struct *queue);

/*
 * @Function	checks for buffer if empty
 * @Param		null
 * @Returns		returns if buffer empty
 */
bool cbfifo_empty(CBfifo_struct *queue);


#endif
