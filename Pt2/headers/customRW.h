#ifndef SYSINFOP1_CUSTOMRW_H
#define SYSINFOP1_CUSTOMRW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "../headers/locker.h"
#include "../headers/semaphore.h"

typedef struct param{
    sem_t2 *heap, *blocker;
    lock_t *mutex_rw;
    int *counter, *iteration;
}param_t;

void *reader(void* voidArg);
void *writer(void* voidArg);

#endif //SYSINFOP1_CUSTOMRW_H
