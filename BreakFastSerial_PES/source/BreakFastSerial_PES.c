#include "sysclock.h"
#include "uart.h"
#include "Cbfifo.h"
#include "UI.h"
#include "CBFifo_test.h"
#include "hexdump.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
  sysclock_init();

  // TODO: initialize the UART here
  Init_UART0(BAUD_RATE);

  //cbfifo_test();

  printf("\rAll test cases passed \n\r");

  printf("\rStarting Program..\n\r");
  printf("\n\r Welcome to BreakfastSerial.\n\n\r Enter commands:\n\r 'Author' - Prints your name. \n\r 'Dump' - Prints Hexdump for the memory you request\r\n 'Help' - Reprints the command menu.\n\r ........................................................ \n\r");

  //char str[] = "Welcome to BreakfastSerial!\r\n";
  //send_String(str, sizeof(str));
  // enter infinite loop
  while (1) {

	  printf("\n\r ? ");
	  accumulate();
  }
  return 0 ;
}
