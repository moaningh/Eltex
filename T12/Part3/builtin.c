#include "shell.h"

int handle_builtin_commands(char *args[]) {
    if (args[0] == NULL) {
        return 1;
    }
    
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] != NULL) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        } else {
            printf("cd: требуется аргумент\n");
        }
        return 1;
    }
    
    if (strcmp(args[0], "exit") == 0) {
        printf("Выход из оболочки\n");
        exit(0);
    }
    
    if (strcmp(args[0], "help") == 0) {
        printf("Простой командный интерпретатор\n");
        printf("Поддерживаемые функции:\n");
        printf("  - Одиночные команды с аргументами\n");
        printf("  - Конвейеры команд (|)\n");
        printf("  - Встроенные команды: cd, exit, help\n");
        printf("Пример: ls -la | grep a\n");
        return 1;
    }
    
    return 0;
}

void execute_single_command(char *command) {
    char *args[MAX_ARGS];
    pid_t pid;
    
    parse_command(command, args);
    
    if (handle_builtin_commands(args)) {
        return;
    }
    
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        return;
    }
    
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}