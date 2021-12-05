#include "../headers/semaphore.h"

void sem_init_(sem_t2 *sem, unsigned int value){
    sem->value = value;
    lock_init(sem->mutex);
}

void sem_wait_(sem_t2 *sem){
    test_and_test_and_set_lock(sem->mutex);
    if(sem->value <= 0) {
        unlock(sem->mutex);
        while (sem->value <= 0);
        sem_wait_(sem);
    }else{
        sem->value--;
        unlock(sem->mutex);
    }
}

void sem_post_(sem_t2 *sem){
    test_and_test_and_set_lock(sem->mutex);
    sem->value++;
    unlock(sem->mutex);
}
