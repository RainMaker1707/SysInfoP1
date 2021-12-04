//
// Created by RainMaker on 24/11/2021.
//

#ifndef SYSINFOP1_PHILOSOPHERS_H
#define SYSINFOP1_PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct param{
    int id, N;
    pthread_mutex_t *chopsticks;
}param_t;

void eat();
void think();
void *party(void* voidArg);

#endif //SYSINFOP1_PHILOSOPHERS_H
