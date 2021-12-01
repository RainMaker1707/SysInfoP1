#include "rw.h"

#define NREAD 2560
#define NWRITE 640

void *reader(void* voidArg){
    param_t* arg = (param_t*)voidArg;
    while(true){
        sem_wait(arg->blocker);
        pthread_mutex_lock(arg->mutex_rw);
        *arg->counter += 1;
        if(*arg->counter == 1) sem_wait(arg->heap); // first reader accesses
        pthread_mutex_unlock(arg->mutex_rw);
        if(*arg->iteration == NREAD) return NULL;
        *arg->iteration += 1; // inc after because of reader work is outside the critical path
        # ifdef DEBUG
        printf("Iteration Reader: %d\n", *arg->iteration);
        # endif
        sem_post(arg->blocker);
        while(rand() > RAND_MAX/10000); // reader work simulation
        *arg->counter -= 1;
        if(*arg->counter == 0) sem_post(arg->heap); // last reader leaves
        pthread_mutex_unlock(arg->mutex_rw);
    }
}

void *writer(void* voidArg){
    param_t* arg = (param_t*)voidArg;
    while(true){
        pthread_mutex_lock(arg->mutex_rw);
        *arg->counter += 1;
        if(*arg->counter == 1) sem_wait(arg->blocker);
        pthread_mutex_unlock(arg->mutex_rw);
        sem_wait(arg->heap);
        while(rand() > RAND_MAX/10000); // Writer work simulation
        *arg->iteration += 1;
        # ifdef DEBUG
        printf("Iteration writer: %d\n", *arg->iteration);
        # endif
        if(*arg->iteration == NWRITE) return NULL;
        sem_post(arg->heap);
        pthread_mutex_lock(arg->mutex_rw);
        *arg->counter -= 1;
        if(*arg->counter == 0) sem_post(arg->blocker); // leave access to reader
        pthread_mutex_unlock(arg->mutex_rw);
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("You have to pass two arguments at the program.\n First one is writer thread number (int)\n Second one is reader threads number (int)\n");
        return EXIT_FAILURE;
    }
    // malloc of all shared variables
    int reader_access = 0, writer_access = 0, w_iter = 0, r_iter = 0;
    int reader_number = (int)strtol(argv[2], &argv[3] - 1, 10);
    int writer_number = (int)strtol(argv[1], &argv[2] - 1, 10);
    # ifdef DEBUG
    printf("R: %d -- W: %d\n", reader_number, writer_number); // TODO rm
    # endif
    // mutex and semaphore
    sem_t heap, blocker;
    pthread_mutex_t mutex_rw;
    sem_init(&heap, 0, 1);
    sem_init(&blocker, 0, 1);
    pthread_t writers[reader_number];
    pthread_t readers[writer_number];
    pthread_mutex_init(&mutex_rw, NULL);
    param_t *w_args = (param_t*)malloc(sizeof(param_t));
    if(!w_args) return EXIT_FAILURE;
    w_args->mutex_rw = &mutex_rw;
    w_args->counter = &writer_access;
    w_args->blocker = &blocker;
    w_args->heap = &heap;
    w_args->iteration = &w_iter;
    for(int i = 0; i < writer_number; i++ ) pthread_create(&writers[i], NULL, &writer, (void*)w_args);
    param_t *r_args = (param_t*)malloc(sizeof(param_t));
    if(!r_args) return EXIT_FAILURE;
    r_args->mutex_rw = &mutex_rw;
    r_args->counter = &reader_access;
    r_args->blocker = &blocker;
    r_args->heap = &heap;
    r_args->iteration = &r_iter;
    for(int i = 0; i < reader_number; i++ ) pthread_create(&readers[i], NULL, &reader, (void*)r_args);
    // Waiting for all threads finished;
    for(int i = 0; i< writer_number; i++)pthread_join(writers[i], NULL);
    for(int i = 0; i< reader_number; i++)pthread_join(readers[i], NULL);
    //garbage
    sem_destroy(&heap);
    sem_destroy(&blocker);
    pthread_mutex_destroy(&mutex_rw);
    return EXIT_SUCCESS;
}