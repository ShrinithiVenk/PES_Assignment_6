#ifndef UI_H_
#define UI_H_

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "hexdump.h"

#define VERSION_TAG 00
#define BUILD_MACHINE 00
#define BUILD_DATE 00
#define GIT_LOG 00



void author(int argc, char *argv[]);
void dump(int argc, char *argv[]);
void invalid(int argc, char *argv[]);
void help(int argc, char *argv[]);
void info(int argc, char *argv[]);
void Command_Process(char *input_char);



#endif /* UI_H_ */
