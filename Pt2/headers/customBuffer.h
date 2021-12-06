#ifndef SYSINFOP1_CUSTOMBUFFER_H
#define SYSINFOP1_CUSTOMBUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include "../headers/locker.h"
#include "../headers/semaphore.h"



typedef struct param{
    int *index, *counter;
    int *buffer;
    sem_t2 *free_p, *new_elem_sig;
    lock_t *mutex_buf, *mutex_pc;
}param_t;

void* producer(void* voidArg);
void *consumer(void* voidArg);

#endif //SYSINFOP1_CUSTOMBUFFER_H
