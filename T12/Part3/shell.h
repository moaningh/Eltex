#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_COMMANDS 10

int split_commands(char *input, char *commands[]);
void parse_command(char *command, char *args[]);

void execute_pipeline(char *commands[], int num_commands);
void execute_single_command(char *command);

int handle_builtin_commands(char *args[]);

#endif