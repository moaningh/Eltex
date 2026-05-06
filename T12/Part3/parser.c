#include "shell.h"

int split_commands(char *input, char *commands[]) {
    int count = 0;
    char *token;
    
    token = strtok(input, "|");
    while (token != NULL && count < MAX_COMMANDS) {
        while (*token == ' ') token++;
        char *end = token + strlen(token) - 1;
        while (end > token && *end == ' ') end--;
        *(end + 1) = '\0';
        
        commands[count] = token;
        count++;
        token = strtok(NULL, "|");
    }
    
    return count;
}

void parse_command(char *command, char *args[]) {
    int i = 0;
    char *token;
    
    token = strtok(command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}