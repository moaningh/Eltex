#include "shell.h"

int main() {
    char input[MAX_INPUT];
    char *commands[MAX_COMMANDS];
    
    printf("Командный интерпретатор с поддержкой конвейера\n");
    printf("Пример: ls -la | grep a\n");
    printf("Встроенные команды: cd, exit, help\n\n");
    
    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\nВыход\n");
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        if (strlen(input) == 0) {
            continue;
        }
        
        char input_copy[MAX_INPUT];
        strcpy(input_copy, input);
        
        if (strchr(input_copy, '|') != NULL) {
            strcpy(input_copy, input);
            int num_commands = split_commands(input_copy, commands);
            
            if (num_commands > 0) {
                execute_pipeline(commands, num_commands);
            }
        } else {
            execute_single_command(input);
        }
    }
    
    return 0;
}