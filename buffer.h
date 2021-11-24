//
// Created by RainMaker on 24/11/2021.
//

#ifndef SYSINFOP1_BUFFER_H
#define SYSINFOP1_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>



typedef struct param{
    int *number, *index, *counter;
    int *buffer;
    sem_t *empty, *full;
    pthread_mutex_t *mutex_buf, *mutex_pc;
}param_t;

void* producer(void* voidArg);
void *consumer(void* voidArg)

#endif //SYSINFOP1_BUFFER_H
