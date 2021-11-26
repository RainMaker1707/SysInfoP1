//
// Created by RainMaker on 24/11/2021.
//

#ifndef SYSINFOP1_RW_H
#define SYSINFOP1_RW_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct param{

}param_t;

void reader(void* voidArg);
void writer(void* voidArg);

#endif //SYSINFOP1_RW_H
