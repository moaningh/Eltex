#include "stall.h"
#include "logger.h"
#include "customer.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NEED_MIN 9900
#define NEED_MAX 10100

extern int customer_finished;
extern pthread_mutex_t mutex_finished;

int random_number(int min, int max);

void* customer_thread(void *arg){
    int id = *(int *)arg;
    free(arg);
    char thread_name[32];
    snprintf(thread_name, sizeof(thread_name), "Покупатель %d", id);
    int need = random_number(NEED_MIN, NEED_MAX);
    char log_buf[256];
    
    snprintf(log_buf, sizeof(log_buf), "создан, начальная потребность = %d", need);
    log_action(thread_name, log_buf);
    
    while (need > 0) {
        int bought = 0;
        int stall_index = -1;

        for (int i = 0; i < NUM_STALL; i++){
            if (pthread_mutex_trylock(&stalls[i].mutex) == 0){
                if (stalls[i].goods > 0){
                    stall_index = i;
                    break;
                }
                pthread_mutex_unlock(&stalls[i].mutex);
            }
        }

        if (stall_index == -1){
            usleep(100000);
            continue;
        }

        snprintf(log_buf, sizeof(log_buf), "зашел в ларек %d, количество товаров %d", stall_index, stalls[stall_index].goods);
        log_action(thread_name, log_buf);

        if (stalls[stall_index].goods >= need){
            bought = need;
            stalls[stall_index].goods -= need;
            need = 0;
            snprintf(log_buf, sizeof(log_buf), "скупил %d товаров, потребность стала = %d", bought, need);
            log_action(thread_name, log_buf);
        } else {
            bought = stalls[stall_index].goods;
            need -= stalls[stall_index].goods;
            stalls[stall_index].goods = 0;
            snprintf(log_buf, sizeof(log_buf), "скупил %d товаров, потребность стала = %d", bought, need);
            log_action(thread_name, log_buf);
        }

        pthread_mutex_unlock(&stalls[stall_index].mutex);

        if (need > 0){
            snprintf(log_buf, sizeof(log_buf), "уснул на 2 секунды, потребность = %d", need);
            log_action(thread_name, log_buf);
            sleep(2);
            snprintf(log_buf, sizeof(log_buf), "проснулся после сна, потребность = %d", need);
            log_action(thread_name, log_buf);
        }
    }
    
    snprintf(log_buf, sizeof(log_buf), "потребность утолена, покупатель уходит");
    log_action(thread_name, log_buf);

    pthread_mutex_lock(&mutex_finished);
    customer_finished++;
    pthread_mutex_unlock(&mutex_finished);

    return NULL;
}