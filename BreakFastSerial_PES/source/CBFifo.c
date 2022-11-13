#include "cbfifo.h"

/*//Initializing the structure to use the elements while calling function on cbfifo
CBfifo CBfifo_t ={
		.size = 0,
		.readp = 0,
		.writep = 0,
		.length = 0,
};*/

void cbfifo_Init(CBfifo_struct * queue){
	    queue->write = 0;
		queue->read = 0;
		queue->full = false;
		queue->empty = false;
		queue->length = 0;
}







//int cbfifo_size(CBfifo_struct *queue){
//	return queue->size;
//}



/*
 * @Function	cbfifo_length
 * @Param		none
 * @Returns		Number of bytes currently available to be dequeued from the FIFO
 * @Description	Returns the number of bytes currently on the FIFO.
 */
//size_t cbfifo_length(CBfifo_struct *queue){
//
//	size_t value = 0;
//	if(queue->full_queue){
//		value = MAXSIZE;
//	}
//	else if(queue->writep >= queue->readp){
//		value = queue->writep - queue->readp;
//	}
//	else{
//		value = MAXSIZE - (queue->readp - queue->writep);
//	}
//	return value;
//}



/*
 * @Function	cbfifo_enqueue
 * @Param		buf - The pointer to the location from where data is to be entered in
 * 					  the fifo
 * 				nbytes - Number of bytes to be enqueued in fifo
 * @Returns		The number of bytes actually copied, which will be between 0 and nbyte.
 * @Description	Enqueues data onto the FIFO, up to the limit of the available FIFO
 * 				capacity.
 */
size_t cbfifo_enqueue(CBfifo_struct *queue, const void *str, size_t nbytes)
{
	char *buff = (char *) str;
	uint32_t masking_state;
	uint8_t e= 0;

	if(buff == NULL)			//error if null string is entered
	{
		return -1;
	}

	else
	{

		if(nbytes < 0)				//error if bytes entered are negative
		{
			return -1;
		}

		else
		{
			if(queue->full)		//Buffer Full
			{
				queue->write = 0;
				return 0;
			}
			else
			{
				if(nbytes >= ((BUFFER_SIZE) - (queue->length)))   //if nbytes > remaining size of buf
				{ nbytes = (BUFFER_SIZE) - (queue->length);
				queue->full = true;
				}

				for(e=0;e<nbytes;e++)
					//writing to the buffer
				{
					queue->buffer_array[queue->write] = buff[e];
					queue->write = (queue->write + 1) & (BUFFER_SIZE-1);
					// protect q->Size++ operation from preemption
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
}




/*
 * @Function	cbfifo_dequeue
 * @Param		buf - The pointer to the location where the dequeued data is to be fetched
 * 				nbytes - Number of bytes to be dequeued from fifo
 * @Returns		The number of bytes actually copied, which will be between 0 and nbyte.
 * @Description	Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * 				FIFO. Removed data will be copied into the buffer pointed to by buf.
 */
size_t cbfifo_dequeue(CBfifo_struct *queue, void *str, size_t nbytes)
{
	char *buff = (char *) str;
	uint32_t masking_state;
	int e = 0;	//error if bytes entered are negative

	if(buff == NULL)
	{
		return -1;
	}

	else
	{
		if(nbytes < 0)
		{
			return -1;
		}


		else
		{
			if(!(queue->length))					//if the buffer is empty, reset pointers
			{
				queue->write = 0; queue->read = 0; queue->full=0;//queue->len = 0;
				return 0;
			}
			else
			{
				if(nbytes > (queue->length))		//if nbytes > length of buffer
				{
					nbytes = (queue->length);
					//queue->is_empty = true;
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
}



/*
 * @Function	cbfifo_capacity
 * @Param		none
 * @Returns		the current capacity of the fifo in bytes
 * @Description	Returns the current capacity of the fifo
 */
size_t cbfifo_length(CBfifo_struct *queue)
{
	return queue->length;
}

//Returns buff_size of the buffer
size_t cbfifo_capacity()
{
	return BUFFER_SIZE;
}

bool cbfifo_full(CBfifo_struct *queue){
	return (cbfifo_length(queue) == BUFFER_SIZE);
}

bool cbfifo_empty(CBfifo_struct *queue){
	return (cbfifo_length(queue) == 0);
}
