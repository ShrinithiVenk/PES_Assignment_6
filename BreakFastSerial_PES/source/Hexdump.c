#include "Hexdump.h"

/**
 * @Function: 	 hexdump()
 * @Parameters:  *add   - It is the pointer to the location from where the hex dump is to be executed
 * 			 	 nbytes - It is the number of bytes which to be dumped from the location pointed by *loc
 * @Description: The function returns the hex dump from the *loc pointer in the memory till the bytes given
 * 			  	 by the user. It would return the hex dump at in the buffer or array to which *str points to.
 * 			  	 Function would return empty *str in the case of error when *str is not large enough to accomodate
 * 			  	 the entire hex dump.
 */
void hexdump(const void *addr, size_t nbytes){

	  const uint8_t *start_ptr = (uint8_t*) addr;

		  for(int i = 0; i< nbytes; i++)
		  {
			  if (i%16 ==0)
			  {
				  uint16_t H = ((uint32_t)(start_ptr+i) & 0xFFFF0000)>>16;
				  uint16_t L = ((uint32_t)(start_ptr+i) & 0x0000FFFF);
				  printf("\n\r %04x", (uint16_t)(H));
				  printf("_%04x : ", (uint16_t)(L));
			  }
			  printf("%02x ", *(start_ptr+i));
		  }
		  printf("\n\r");
	}

