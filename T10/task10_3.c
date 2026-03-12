#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    
    printf("Simple Shell Interpreter\n");
    printf("Type 'exit' to quit\n");
    
    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        if (strlen(input) == 0) {
            continue;
        }
        
        int arg_count = 0;
        char *token = strtok(input, " ");
        
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;
        
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("fork failed");
            continue;
        }
        else if (pid == 0) {
            printf("Child process (PID: %d) executing: %s\n", getpid(), args[0]);
            
            if (execvp(args[0], args) == -1) {
                perror("execution failed");
                exit(1);
            }
        }
        else {
            int status;
            wait(&status);
            
            printf("Child process (PID: %d) finished. ", pid);
            
            if (WIFEXITED(status)) {
                printf("Exit status: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Terminated by signal: %d\n", WTERMSIG(status));
            }
        }
    }
    
    return 0;
}