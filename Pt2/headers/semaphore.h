#ifndef SYSINFOP1_SEMAPHORE_H
#define SYSINFOP1_SEMAPHORE_H

#include <stdlib.h>
#include <stdio.h>
#include "../headers/locker.h"

typedef struct semaphore{
    unsigned int value;
    lock_t *mutex;
}sem_t2;

void sem_init_(sem_t2 *sem, unsigned int value);
void sem_wait_(sem_t2 *sem);
void sem_post_(sem_t2 *sem);

#endif //SYSINFOP1_SEMAPHORE_H
