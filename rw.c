#include "rw.h"

void *reader(void* voidArg){
    param_t* arg = (param_t*)voidArg;
    return NULL;
}

void *writer(void* voidArg){
    param_t* arg = (param_t*)voidArg;
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("You have to pass two arguments at the program.\n First one is writer thread number (int)\n Second one is reader threads number (int)\n");
        return EXIT_FAILURE;
    }
    // malloc of all shared variables
    int reader_access = 0;
    int writer_access = 0;
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
    for(int i = 0; i < writer_number; i++ ) pthread_create(&writers[i], NULL, &writer, (void*)w_args);
    param_t *r_args = (param_t*)malloc(sizeof(param_t));
    if(!r_args) return EXIT_FAILURE;
    r_args->mutex_rw = &mutex_rw;
    r_args->counter = &reader_access;
    r_args->blocker = &blocker;
    r_args->heap = &heap;
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