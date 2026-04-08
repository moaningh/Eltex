#include "stall.h"
#include "logger.h"
#include "loader.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define RESTOCK_AMOUNT 200

extern int customer_finished;
extern int loader_running;
extern pthread_mutex_t mutex_finished;

void* loader_thread(){
    char thread_name[] = "Погрузчик";

    while (loader_running){
        int stall_index = rand() % NUM_STALL;

        pthread_mutex_lock(&stalls[stall_index].mutex);

        char log_buf[256];
        snprintf(log_buf, sizeof(log_buf), "зашел в ларек %d, текущее количество товаров %d", stall_index, stalls[stall_index].goods);
        log_action(thread_name, log_buf);
        stalls[stall_index].goods += RESTOCK_AMOUNT;
        snprintf(log_buf, sizeof(log_buf), "пополнил ларек %d на %d товаров, текущее количество товаров %d", stall_index, RESTOCK_AMOUNT, stalls[stall_index].goods);
        log_action(thread_name, log_buf);

        pthread_mutex_unlock(&stalls[stall_index].mutex);
        snprintf(log_buf, sizeof(log_buf), "уснул на 1 секунду");
        log_action(thread_name, log_buf);
        sleep(1);
        snprintf(log_buf, sizeof(log_buf), "проснулся");
        log_action(thread_name, log_buf);

        pthread_mutex_lock(&mutex_finished);
        if (customer_finished >= 3){
            pthread_mutex_unlock(&mutex_finished);
            break;
        }
        pthread_mutex_unlock(&mutex_finished);
    }
    
    log_action("Погрузчик", "завершил работу");
    return NULL;
}