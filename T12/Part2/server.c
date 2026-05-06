#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "my_fifo"

int main() {
    int fd;
    char message[] = "Hi!";
    
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    
    printf("Сервер: Именованный канал %s создан\n", FIFO_NAME);
    
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        unlink(FIFO_NAME);
        exit(1);
    }
    
    printf("Сервер: Канал открыт на запись\n");
    
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd);
        unlink(FIFO_NAME);
        exit(1);
    }
    
    printf("Сервер: Строка \"%s\" записана в канал\n", message);
    
    close(fd);
    
    printf("Сервер: Работа завершена\n");
    
    return 0;
}