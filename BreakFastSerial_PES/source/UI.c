#include "UI.h"

/**
 * @Function: 	 Function that gives the author name
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void author(int argc, char *argv[])
{
	printf("\r\n Shrinithi Venkatesan\n");
}

/**
 * @Function: 	 Function that entails comments to let the user know that invalid command in entered
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void invalid(int argc, char *argv[])
{
	printf("Invalid Command: %s\r\n", argv[0]);
}

/**
 * @Function: 	 Function that generates hendump
 * @Parameters:  argc, *argv
 * @Returns   :  Hexdump
 */
void dump(int argc, char *argv[])
{
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

/**
 * @Function: 	 Function that prints command menu
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void menu(int argc, char *argv[])
{
	printf("\n\r This is BreakfastSerial!\n\n\r Enter commands:\n\r 'Author' - Prints your name. \n\r 'Dump'   - Prints Hexdump for the memory you request\n\r 'Info'   - Prints Information on the build parameters.\n\r");
}

/**
 * @Function: 	 Function that information on the git build parameters.
 * @Parameters:  argc, *argv
 * @Returns   :  Null
 */
void info(int argc, char *argv[])
{
	printf("\r Version tag: %s \n\r Built Machine: %s \n\r Built Date: %s \r\n", VERSION_TAG, VERSION_BUILD_MACHINE, VERSION_BUILD_DATE);
	printf("\r Commit ID: %s \r\n", GIT_LOG);
}


//Command Table
static const commands_struct command[] =
{
		{"Author", author},
		{"Dump", dump},
		{"Help", menu},
		{"Info", info},
		{" ", invalid}
};

//Gets the total count of commands
static const int command_count = sizeof(command)/sizeof(commands_struct);

/**
 * @Function: 	 Processes the features that includes handling backspaces and nullspaces.
 * @Parameters:  Null
 * @Returns   :  Null
 */
void process_Command_process(void){
	char temp_buff[800];
	char *ptr_temp = &temp_buff[0];
	uint8_t ch;

	while(ch != '\r'){
		//In loop until terminating character is received
		while(cbfifo_empty(&RxQ)){
			;//Wait until Rx queue is empty to handle the user input commands
		}
     	cbfifo_dequeue(&RxQ, &ch, 1);
		putchar(ch);
		if((ch != '\r') && (ch != '\n')){
			//Not handling backspace here.
			*ptr_temp = (char)ch;
			ptr_temp++;
			*ptr_temp = '\0';
		}

		if(!(UART0->C2 & UART0_C2_TIE_MASK)){
			UART0->C2 |= UART0_C2_TIE(1);
		}

		if(ch == '\r'){
			ch = '\n';
			printf("\r\n");
			break;
		}
	}

	Command_Process(temp_buff);
	ptr_temp = &temp_buff[0];			//Resetting the pointer back to initial location for next accumulation
}

/**
 * @Function: 	 Function that processes the input commands from the user
 * @Parameters:  *input_char
 * @Returns   :  Null
 */
void Command_Process(char *input_char)
{
	char *start_ptr = &input_char[0];
	char *end_ptr = (char *) malloc(sizeof(end_ptr));

	//Find the end pointer
	for(end_ptr = input_char; *end_ptr != '\0'; end_ptr++);

	bool flag = false;
	char *argv[10];
	int argc = 0;
	memset(argv, 0, sizeof(argv));
	//initializing argv with 0

	for(start_ptr = input_char; start_ptr < end_ptr; start_ptr++){
		if(*start_ptr == ' '){
			//Check on spaces
			if(!flag){
				*start_ptr = ' ';
				//Ignore spaces if not a token
			}
			else{
				*start_ptr = '\0';
				//Fill up the space after token with \0
				flag = false;
			}
		}
		else{
			//Managing the token from the input string token
			if(!flag){
				argv[argc] = start_ptr;
				//pointing to first argument on the accumulated buffer
				argc++;
				//Increment argc for next argument
			}
			flag = true;
		}
	}

	argv[argc] = NULL;
	if (argc == 0){
		//Return nothing when No command entered
		return;
	}

	//Dispatch argc/argv to handler
	for(int i=0; i<command_count; i++){
		if(strcasecmp(argv[0], command[i].name) == 0){
			command[i].handler(argc, argv);
			//calls corresponding function handler
			start_ptr = &input_char[0];
			return;
		}
	}

	//invalid case when commands entered are not recognized
	invalid(argc, argv);
	start_ptr = &input_char[0];
	return;
}

