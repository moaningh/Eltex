#include "stall.h"
#include <stdio.h>
#include <stdlib.h>

#define INIT_MIN 900
#define INIT_MAX 1100

int random_number (int min, int max){
    return min + rand() % (max - min + 1);
}

void init_stall() {
    for (int i = 0; i < NUM_STALL; i++){
        stalls[i].goods = random_number (INIT_MIN, INIT_MAX);
        pthread_mutex_init(&stalls[i].mutex, NULL);
        pthread_cond_init(&stalls[i].cond, NULL);
        printf("Ларек %d инициализирован с %d товаров!\n", i, stalls[i].goods);
    }
}

void destroy_stall() {
    for (int i = 0; i < NUM_STALL; i++){
        pthread_mutex_destroy(&stalls[i].mutex);
        pthread_cond_destroy(&stalls[i].cond);
    }
}