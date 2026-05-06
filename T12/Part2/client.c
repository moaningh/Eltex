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
    char buffer[100];
    
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    printf("Клиент: Канал открыт на чтение\n");
    
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read");
        close(fd);
        exit(1);
    }
    
    printf("Клиент: Получена строка: %s\n", buffer);
    
    close(fd);
    
    if (unlink(FIFO_NAME) == -1) {
        perror("unlink");
        exit(1);
    }
    
    printf("Клиент: Канал удален, работа завершена\n");
    
    return 0;
}