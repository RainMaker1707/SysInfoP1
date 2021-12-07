#include "../headers/semaphore.h"

void sem_init_(sem_t2 *sem, unsigned int value){
    sem->value = value;
    lock_init(sem->mutex); // init associated mutex
}

void sem_wait_(sem_t2 *sem){
    test_and_test_and_set_lock(sem->mutex); //lock semaphore to synchronize concurrent threading
    if(sem->value <= 0) {
        unlock(sem->mutex);
        while (sem->value <= 0);
        sem_wait_(sem); //recursion to retest the sem lock
    }else{
        sem->value--; // critical path
        unlock(sem->mutex); // unlock mutex
    }
}

void sem_post_(sem_t2 *sem){
    test_and_test_and_set_lock(sem->mutex); //lock mutex to synchronize concurrent threading
    sem->value++; // critical path
    unlock(sem->mutex); // unlock mutex
}
