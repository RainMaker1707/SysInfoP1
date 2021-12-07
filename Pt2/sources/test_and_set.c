#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../headers/locker.h"

#define TOTAL 6400
lock_t *lock_v;

void *threading(void *arg){
    printf("Enter threads");
    int n_iteration = *(int *)arg;
    int i=0;
    printf("%d\n", n_iteration);
    while(i < n_iteration){
        lock(lock_v);
        printf("%d\n", n_iteration);
        while(rand() > RAND_MAX/10000);
        unlock(lock_v);
        i++;
    }
    return NULL;
}


int main(int argc, char *argv[]){

    if(argc != 1) return EXIT_FAILURE;
    int thread_number = (int)strtol(argv[1], &argv[2]-1, 10);

    pthread_t threads[thread_number];
    int round = TOTAL/thread_number;

    printf("start\n");

    lock_v = (lock_t*)malloc(sizeof(lock_t));
    if(!lock_v) return EXIT_FAILURE;
    lock_init(lock_v);

    printf("ok\n");

    for(int i=0; i < thread_number; i++) {
        if(i == thread_number-1) round += TOTAL % thread_number;
        pthread_create(&threads[i], NULL, threading, (void *)&round);
    }
    for(int i=0; i < thread_number; i++) pthread_join(threads[i], NULL);
    free(lock_v);
}

