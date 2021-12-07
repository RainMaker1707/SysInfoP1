#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../headers/locker.h"

#define TOTAL 6400
lock_t *lock_v;

void *threading(void *arg){
    int *n_iteration = (int *)arg; // convert  iteration number
    for(int i= 0; i < *n_iteration; i++){
        //critical path
        test_and_test_and_set_lock(lock_v);  //lock mutex
        while(rand() > RAND_MAX/10000); // work simulation
        unlock(lock_v); //unlock mutex
    }
    return NULL;
}


int main(int argc, char *argv[]){
    if(argc != 2) return EXIT_FAILURE;

    int thread_number = (int)strtol(argv[1], &argv[2]-1, 10);
    pthread_t threads[thread_number];
    int round = TOTAL/thread_number; // divide total iteration number to fit in thread number

    // init mutex
    lock_v = (lock_t*)malloc(sizeof(lock_t));
    if(!lock_v) return EXIT_FAILURE;
    lock_init(lock_v);

    //init threads
    for(int i=0; i < thread_number; i++) {
        if(i == thread_number-1) round += TOTAL % thread_number;
        pthread_create(&threads[i], NULL, &threading, (void *)&round);
    }

    //wait for all threads
    for(int i=0; i < thread_number; i++) pthread_join(threads[i], NULL);

    //garbage
    free(lock_v);
}



