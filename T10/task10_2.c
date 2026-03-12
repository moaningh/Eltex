#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int status;

    pid_t process1 = fork();
    if (process1 == 0){
        printf("Process1 PID = %d, PPID = %d\n", getpid(), getppid());

        pid_t process3 = fork();
        if (process3 == 0){
            printf("Process3 PID = %d, PPID = %d\n", getpid(), getppid());
            exit(5);
        }

        pid_t process4 = fork();
        if (process4 == 0){
            printf("Process4 PID = %d, PPID = %d\n", getpid(), getppid());
            exit(5);
        }

        wait(&status);
        wait(&status);
        exit(5);
    }
    pid_t process2 = fork();
        if (process2 == 0){
            printf("Process2 PID = %d, PPID = %d\n", getpid(), getppid());
            
            pid_t process5 = fork();
            if (process5 == 0){
                printf("Process5 PID = %d, PPID = %d\n", getpid(), getppid());
                exit(5);
            }

            wait(&status);
        }

    return 0;
}