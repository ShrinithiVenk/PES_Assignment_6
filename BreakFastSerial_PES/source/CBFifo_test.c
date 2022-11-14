#include <assert.h>
#include<stdlib.h>
#include "cbfifo_test.h"
#include "cbfifo.h"
#include "UART.h"
#include "UI.h"

/*
 * @Function	Passes all the necessary test cases to check the cbfifo funtions.
 * @Param		Null
 * @Returns		Null
 */

void cbfifo_test()
{
			 char *string = "Welcome to BreakFastSerial!";
			 char buff_size[256];
			 size_t bytes;

			  CBfifo_struct *queue = (CBfifo_struct *) malloc(sizeof(CBfifo_struct));
			  cbfifo_Init(queue);

			  //enqueueing bytes
		      bytes = cbfifo_enqueue(queue, "Breakfastserial", 15);
			  assert(bytes == 15);
			  assert(cbfifo_length(queue) == 15);

			  bytes = cbfifo_enqueue(queue, "to", 2);
			  assert(bytes == 2);
			  assert(queue->length == 17);

			  //dequeueing bytes
	       	  bytes = cbfifo_dequeue(queue, &buff_size, 3);
	       	  assert(bytes == 3);
	       	  assert(queue->length == 14);
	       	  assert(buff_size[0] == 'B');
	       	  assert(buff_size[1] == 'r');
	       	  assert(buff_size[2] == 'e');

	       	  //making the fifo empty
	       	  bytes = cbfifo_dequeue(queue, &buff_size, 14);
	       	  assert(bytes == 14);
	          assert(queue->length == 0);

	       	  //checking if correct string is enqueued and of no. of bytes specified
	       	  bytes = cbfifo_enqueue(queue, string, 8);
	       	  assert(bytes == 8);
	       	  assert(queue->buffer_array[0] == 'W');
	       	  assert(queue->buffer_array[1] == 'e');
	       	  assert(queue->buffer_array[2] == 'l');
	          assert(queue->buffer_array[3] == 'c');
	          assert(queue->buffer_array[4] == 'o');
	          assert(queue->buffer_array[5] == 'm');
	          assert(queue->buffer_array[6] == 'e');
	          assert(queue->buffer_array[7] == ' ');

	          //enqueueing null string
//	       	  bytes = cbfifo_enqueue(queue, NULL, 2);
//	       	  assert(bytes == -1);
//
//	       	//enqueueing negative nbytes
//	       	  bytes = cbfifo_enqueue(queue, string, -1);
//	       	  assert(bytes == -1);

}
