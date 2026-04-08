#ifndef STALL_H
#define STALL_H

#include <pthread.h>

#define NUM_STALL 5

int random_number (int min, int max);
void init_stall(void);
void destroy_stall(void);

typedef struct {
    int goods;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

} Stall;

extern Stall stalls [NUM_STALL];

#endif