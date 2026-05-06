#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    
    if (pid > 0) {
        close(fd[0]);
        
        char message[] = "Hi!";
        write(fd[1], message, strlen(message) + 1);
        
        close(fd[1]);
        
        wait(NULL);
        
        printf("Родительский процесс завершен\n");
        
    } else {
        close(fd[1]);
        
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        
        printf("Дочерний процесс получил: %s\n", buffer);
        
        close(fd[0]);
        
        printf("Дочерний процесс завершен\n");
        exit(0);
    }
    
    return 0;
}