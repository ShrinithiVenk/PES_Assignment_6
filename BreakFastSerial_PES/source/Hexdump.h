#ifndef HEXDUMP_H_
#define HEXDUMP_H_
#include <stdio.h>
/**
 * @Function: 	 Takes the starting address and length for the requested memory space and generates the Hex dump for the memory requested as 16 bytes per line.
 * @Parameters:  *add, nbytes
 * @Returns   :   Hexdump of the requested memory space
 */
void hexdump(const void *addr, size_t nbytes);

#endif /* HEXDUMP_H_ */
