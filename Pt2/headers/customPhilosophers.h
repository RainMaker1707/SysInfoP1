#ifndef SYSINFOP1_CUSTOMPHILOSOPHERS_H
#define SYSINFOP1_CUSTOMPHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../headers/locker.h"

typedef struct param{
    int id, N;
    lock_t *chopsticks;
}param_t;

void eat();
void think();
void *party(void* voidArg);

#endif //SYSINFOP1_CUSTOMPHILOSOPHERS_H
