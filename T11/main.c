#include "stall.h"
#include "customer.h"
#include "loader.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

Stall stalls [NUM_STALL];
int customer_finished = 0;
pthread_mutex_t mutex_finished = PTHREAD_MUTEX_INITIALIZER;
int loader_running = 1;

void init_stall(void);
void destroy_stall(void);

int main(){
    srand(time(NULL));

    init_stall();

    pthread_t customers[3];
    for (int i = 0; i < 3; i++){
        int *id = malloc(sizeof(int));
        *id = i +1;
        pthread_create(&customers[i], NULL, customer_thread, id);
    }

    pthread_t loader;
    pthread_create(&loader, NULL, loader_thread, NULL);

    for (int i = 0; i < 3; i++){
        pthread_join(customers[i], NULL);
    }

    loader_running = 0;
    pthread_join(loader, NULL);

    destroy_stall();
    pthread_mutex_destroy(&mutex_finished);

    printf("Все покупатели насытелись, программа завершена!\n");

    return 0;
}