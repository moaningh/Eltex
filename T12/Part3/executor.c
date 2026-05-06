#include "shell.h"

void execute_pipeline(char *commands[], int num_commands) {
    int pipes[2 * (num_commands - 1)];
    pid_t pid;
    int i;
    
    for (i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes + i * 2) == -1) {
            perror("pipe");
            exit(1);
        }
    }
    
    for (i = 0; i < num_commands; i++) {
        char *args[MAX_ARGS];
        parse_command(commands[i], args);
        
        if (handle_builtin_commands(args)) {
            fprintf(stderr, "Встроенные команды не поддерживаются в конвейере\n");
            continue;
        }
        
        pid = fork();
        
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        
        if (pid == 0) {
            if (i > 0) {
                if (dup2(pipes[(i - 1) * 2], 0) == -1) {
                    perror("dup2 stdin");
                    exit(1);
                }
            }
            
            if (i < num_commands - 1) {
                if (dup2(pipes[i * 2 + 1], 1) == -1) {
                    perror("dup2 stdout");
                    exit(1);
                }
            }
            
            for (int j = 0; j < 2 * (num_commands - 1); j++) {
                close(pipes[j]);
            }
            
            execvp(args[0], args);
            
            perror("execvp");
            exit(1);
        }
    }
    
    for (i = 0; i < 2 * (num_commands - 1); i++) {
        close(pipes[i]);
    }
    
    for (i = 0; i < num_commands; i++) {
        wait(NULL);
    }
}