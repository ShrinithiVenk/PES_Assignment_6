#include "cbfifo.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <MKL25Z4.h>
/*
 * @Function	Initializes the structure for cbfifo.
 * @Param		Null
 * @Returns		Null
 */
void cbfifo_Init(CBfifo_struct * queue){
	queue->write = 0;
	queue->read = 0;
	queue->full = 0;
	queue->empty = 0;
	queue->length = 0;
}

/*
 * @Function	Enqueues data onto the FIFO, up to the limit of the available FIFO capacity.
 * @Param		str, nbytes
 * @Returns		The number of bytes enqueued, which will be between 0 and nbyte.
 */
size_t cbfifo_enqueue(CBfifo_struct *queue, const void *str, size_t nbytes)
{
	char *buff = (char *) str;
	uint32_t masking_state;
	uint8_t e= 0;

	//if null string
	if(buff == NULL)
	{
		return -1;
	}
	//if Buffer Full
	else
	{
		if(queue->full)
		{
			queue->write = 0;
			return 0;
		}
		else
		{
			 //if nbytes > size of buffer
			if(nbytes >= ((BUFFER_SIZE) - (queue->length)))
			{ nbytes = (BUFFER_SIZE) - (queue->length);
			queue->full = true;
			}

			for(e=0;e<nbytes;e++)
			//writing to the buffer
			{
				queue->buffer_array[queue->write] = buff[e];
				queue->write = (queue->write + 1) & (BUFFER_SIZE-1);
				// protect queue->length++ operation from preemption
				// save current masking state
				masking_state = __get_PRIMASK();
				// disable interrupts
				__disable_irq();
				// update variable
				queue->length++;
				// restore  interrupt masking state
				__set_PRIMASK(masking_state);
			}
			return nbytes;
		}
	}
}

/*
 * @Function	Dequeues up to nbytes of data from the FIFO.
 * @Param		str, nbtes
 * @Returns		The number of bytes removed, which will be between 0 and nbyte.
 */
size_t cbfifo_dequeue(CBfifo_struct *queue, void *str, size_t nbytes)
{
	char *buff = (char *) str;
	uint32_t masking_state;
	int e = 0;

	//error if bytes entered are negative
	if(buff == NULL)
	{
		return -1;
	}
		else
		{
			//if the buffer is empty
			if(!(queue->length))
			{
				queue->write = 0; queue->read = 0; queue->full=0;
				return 0;
			}
			else
			{
				if(nbytes > (queue->length))
				//if nbytes > length of buffer
				{
					nbytes = (queue->length);
				}

				for(e=0;e<nbytes;e++)
					//reading from the buffer
				{
					buff[e] = queue->buffer_array[queue->read];
					queue->read = (queue->read + 1)&(BUFFER_SIZE-1);
					// save current masking state
					masking_state = __get_PRIMASK();
					// disable interrupts
					__disable_irq();
					// update variable
					queue->length--;
					// restore  interrupt masking state
					__set_PRIMASK(masking_state);
				}
				if(!(queue->length))
				{
					queue->write = 0; queue->read = 0; queue->full = false;
				}
				return nbytes;
			}
		}
	}

/*
 * @Function	Returns the length of the fifo
 * @Param		null
 * @Returns		returns the size of the fifo in bytes
 */
size_t cbfifo_length(CBfifo_struct *queue)
{
	return queue->length;
}

/*
 * @Function	Returns the current capacity of the fifo
 * @Param		null
 * @Returns		the current capacity of the fifo in bytes
 */
size_t cbfifo_capacity()
{
	return BUFFER_SIZE;
}

/*
 * @Function	checks for buffer if full
 * @Param		null
 * @Returns		returns if buffer full
 */
bool cbfifo_full(CBfifo_struct *queue){
	return (cbfifo_length(queue) == BUFFER_SIZE);
}

/*
 * @Function	checks for buffer if empty
 * @Param		null
 * @Returns		returns if buffer empty
 */
bool cbfifo_empty(CBfifo_struct *queue){
	return (cbfifo_length(queue) == 0);
}
