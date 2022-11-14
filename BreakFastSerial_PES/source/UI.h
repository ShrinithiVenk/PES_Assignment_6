#ifndef UI_H_
#define UI_H_
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "hexdump.h"
#include "UART.h"

//Declaration of command handling structure
typedef void (*command_handler_struct)(int, char *argv[]);

/**
 * Structure with states of the command handler
 */
typedef struct{
	const char *name;
	command_handler_struct handler;
}commands_struct;

/**
 * @Function: 	 Function that gives the author name
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void author(int argc, char *argv[]);

/**
 * @Function: 	 Function that generates hendump
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void dump(int argc, char *argv[]);

/**
 * @Function: 	 Function that entails comments to let the user know that invalid command in entered
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void invalid(int argc, char *argv[]);

/**
 * @Function: 	 Function that prints command menu
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void menu(int argc, char *argv[]);

/**
 * @Function: 	 Function that information on the git build parameters.
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void info(int argc, char *argv[]);

/**
 * @Function: 	 Processes the features that includes handling backspaces and nullspaces.
 * @Parameters:  Null
 * @Returns   :  Null
 */
void process_Command_process(void);

/**
 * @Function: 	 Function that processes the input commands from the user
 * @Parameters:  *input_char
 * @Returns   :  Null
 */
void Command_Process(char *input_char);


#endif /* UI_H_ */
