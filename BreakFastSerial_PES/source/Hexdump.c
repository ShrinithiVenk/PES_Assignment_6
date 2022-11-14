#include "Hexdump.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
/**
 * @Function: 	 Takes the starting address and length for the requested memory space and generates the Hex dump for the memory requested as 16 bytes per line.
 * @Parameters:  *add, nbytes
 * @Returns   :   Hexdump of the requested memory space
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

