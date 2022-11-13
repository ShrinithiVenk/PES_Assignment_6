#ifndef CBFIFO_H
#define CBFIFO_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <MKL25Z4.h>

#define BUFFER_SIZE		256					//Static size of cbfifo
//#define min(x,y)	((x)<(y)?(x):(y))

/**
 * The structure stores the necessary elements to track the states of the circular
 * buffer FIFO
 */
typedef struct			//circular buffer structure
{
  char buffer_array[BUFFER_SIZE];
  uint8_t read, write;
  size_t max_len;
  size_t length;
  bool full;
  bool empty;

}CBfifo_struct;



void cbfifo_Init(CBfifo_struct *queue);

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 */
size_t cbfifo_enqueue(CBfifo_struct *queue, const void *str, size_t nbytes);


/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 *
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(CBfifo_struct *queue, void *str, size_t nbytes);


/*
 * Returns the number of bytes currently on the FIFO.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(CBfifo_struct *queue);


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity();


///*
// * @Function	cbfifo_dump_state
// * @Param		none
// * @Returns		none
// * @Description	prints the current state of the fifo for debug purposes
// */
//void cbfifo_dump_state(void);


bool cbfifo_full(CBfifo_struct *queue);

bool cbfifo_empty(CBfifo_struct *queue);

//int cbfifo_size(CBfifo_struct *queue);

#endif /* QUEUE_H_ */
