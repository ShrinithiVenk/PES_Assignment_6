#include "UI.h"
#include "Hexdump.h"
#include <stdio.h>

typedef void (*command_handler_struct)(int, char *argv[]);


//Look-up table data structure
typedef struct{
	const char *name;
	command_handler_struct handler;
}commands_struct;

 void author(int argc, char *argv[]){
	printf("\r\n Shrinithi Venkatesan\n");
}


 void invalid(int argc, char *argv[]){
	printf("Invalid Command: %s\r\n", argv[0]);
}


 void dump(int argc, char *argv[]){


	uint32_t start = 0;
	size_t len = 0;
	if(argc != 3){
		invalid(argc, argv);
		return;
	}
	sscanf(*(&argv[1]), "%x", &start);
	sscanf(*(&argv[2]), "%i", &len);
	hexdump((void*)start, len);
}


 void help(int argc, char *argv[])
 {

	printf("\n\r Welcome to BreakfastSerial.\n\n\r Enter commands:\n\r 'Author' - Prints your name. \n\r 'Dump'    - Prints Hexdump for the memory you request\r\n 'Help'    - Reprints the command menu.\n\r 'Info'   -Prints Information on your GIT Repository \n\r ........................................................ \n\r");
 }


 void info(int argc, char *argv[]){
	printf("Version tag: %s \n\r Built Machine: %s \n\r Built Date: %s \r\n", VERSION_TAG, BUILD_MACHINE, BUILD_DATE);
	printf("Commit ID: %s \r\n", GIT_LOG);
}



//Cmd Look-up table
static const commands_struct command[] = {
		{"Author", author},
		{"Dump", dump},
		{"Help", help},
		{"Info", info},
		{"", invalid}
};

static const int command_count = sizeof(command)/sizeof(commands_struct);


void Command_Process(char *input_char){
	char *start_ptr = &input_char[0];
	char *end_ptr;

	//To find the end pointer
	for(end_ptr = input_char; *end_ptr != '\0'; end_ptr++);

	//Tokenize input in place
	bool flag = false;
	char *argv[10];
	int argc = 0;
	memset(argv, 0, sizeof(argv));		//initializing argv with 0

	for(start_ptr = input_char; start_ptr < end_ptr; start_ptr++){
			if(*start_ptr == ' '){				//Check on spaces
				if(!flag){
					*start_ptr = ' ';					//Ignore spaces if not a token
				}
				else{
					*start_ptr = '\0';			//Fill up the space after token with \0
					flag = false;
				}
			}
			else{							//Managing the token from the input string token
				if(!flag){
					argv[argc] = start_ptr;			//pointing to first argument on the accumulated buffer
					argc++;						//Increment argc for next argument
				}
				flag = true;
			}
	}

	argv[argc] = NULL;
	if (argc == 0){						//No command entered
		return;
	}

	//TODO: Dispatch argc/argv to handler
	for(int i=0; i<command_count; i++){
		if(strcasecmp(argv[0], command[i].name) == 0){
			command[i].handler(argc, argv);					//calls corresponding function handler
			start_ptr = &input_char[0];
			return;
		}
	}

	invalid(argc, argv);
	start_ptr = &input_char[0];
	return;
}

