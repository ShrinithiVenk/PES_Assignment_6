/*
 * breakfast.c - main file that executes the program functions
 *
 * Author Shrinithi Venkatesan
 *
 * Inspired by
 *       1) https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data
 *       2) https://stackoverflow.com/questions/10493411/what-is-bit-masking
 *       3) https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
 *       4) https://unix.stackexchange.com/questions/190175/hexdump-of-a-string-starting-at-new-lines
 *       5) https://stackoverflow.com/questions/44593566/how-to-make-a-command-line-program-in-c
 *       6) Major code reference from Dean Book. https://github.com/alexander-g-dean/ESF
 */

#include "sysclock.h"
#include "uart.h"
#include "Cbfifo.h"
#include "UI.h"
#include "CBFifo_test.h"
#include "MKL25Z4.h"
#include "hexdump.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
  sysclock_init();

  //initialize the UART here
  UART0_Init(BAUD_RATE);
  cbfifo_test();

  printf("\rAll test cases passed \n\r");
  printf("Welcome to BreakfastSerial.\n\r");
  printf("\n\rEnter command:\n\r 'Author' - Prints your name. \n\r 'Dump' - Prints Hexdump for the requested memory\r\n 'Help' - Reprints command menu.\n\r 'Info - Prints info of build parameters. \r\n");

  //enter infinite loop
  while (1) {

	  printf("\n\r? ");
	  process_Command_process();
  }
  return 0 ;
}
