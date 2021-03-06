#include "../headers/customRW.h"
#define NREAD 2560
#define NWRITE 640

lock_t *exclusive;

void *reader(void* voidArg){
    param_t* arg = (param_t*)voidArg;
    while(true){
        test_and_test_and_set_lock(exclusive);
            sem_wait_(arg->blocker);
                test_and_test_and_set_lock(arg->mutex_rw);
                    *arg->counter += 1;
                    if(*arg->counter == 1) sem_wait_(arg->heap); // first reader accesses
                unlock(arg->mutex_rw);
            sem_post_(arg->blocker);
        unlock(exclusive);

        if(*arg->iteration >= NREAD) {
            sem_post_(arg->heap);
            return NULL;
        }
        *arg->iteration += 1; // inc after because of reader work is outside the critical path
        //printf("Iteration Reader: %d\n", *arg->iteration);
        while(rand() > RAND_MAX/10000); // reader work simulation

        test_and_test_and_set_lock(arg->mutex_rw);
            *arg->counter -= 1;
            if(*arg->counter == 0) sem_post_(arg->heap); // last reader leaves
        unlock(arg->mutex_rw);
    }
}

void *writer(void* voidArg){
    param_t* arg = (param_t*)voidArg;
    while(true){
        test_and_test_and_set_lock(arg->mutex_rw);
            *arg->counter += 1;
            if(*arg->counter == 1) sem_wait_(arg->blocker);
        unlock(arg->mutex_rw);

        sem_wait_(arg->heap);
            //printf("Iteration writer: %d\n", *arg->iteration);
            if(*arg->iteration >= NWRITE) {
                sem_post_(arg->blocker);
                sem_post_(arg->heap);
                return NULL;
            }
            *arg->iteration += 1;
            while(rand() > RAND_MAX/10000); // Writer work simulation
        sem_post_(arg->heap);

        test_and_test_and_set_lock(arg->mutex_rw);
            *arg->counter -= 1;
            if(*arg->counter == 0) sem_post_(arg->blocker); // leave access to reader
        unlock(arg->mutex_rw);
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
    sem_t2 *heap = (sem_t2*)malloc(sizeof(sem_t2));
    sem_t2 *blocker = (sem_t2*)malloc(sizeof(sem_t2));
    lock_t *mutex_rw = (lock_t*)malloc(sizeof(lock_t));
    exclusive = (lock_t*)malloc(sizeof(lock_t));
    if(!(heap && blocker && mutex_rw && exclusive)) return EXIT_FAILURE;
    sem_init_(heap, 1);
    sem_init_(blocker, 1);
    pthread_t writers[reader_number];
    pthread_t readers[writer_number];
    lock_init(mutex_rw);
    lock_init(exclusive);

    param_t *w_args = (param_t*)malloc(sizeof(param_t));
    if(!w_args) return EXIT_FAILURE;
    w_args->mutex_rw = mutex_rw;
    w_args->counter = &writer_access;
    w_args->blocker = blocker;
    w_args->heap = heap;
    w_args->iteration = &w_iter;
    for(int i = 0; i < writer_number; i++ ) pthread_create(&writers[i], NULL, &writer, (void*)w_args);

    param_t *r_args = (param_t*)malloc(sizeof(param_t));
    if(!r_args) return EXIT_FAILURE;
    r_args->mutex_rw = mutex_rw;
    r_args->counter = &reader_access;
    r_args->blocker = blocker;
    r_args->heap = heap;
    r_args->iteration = &r_iter;
    for(int i = 0; i < reader_number; i++ ) pthread_create(&readers[i], NULL, &reader, (void*)r_args);
    // Waiting for all threads finished;
    for(int i = 0; i< writer_number; i++)pthread_join(writers[i], NULL);
    for(int i = 0; i< reader_number; i++)pthread_join(readers[i], NULL);
    //garbage
    //printf("W: %d, R: %d\n", *w_args->iteration, *r_args->iteration);
    free(heap);
    free(blocker);
    free(mutex_rw);
    free(w_args);
    free(r_args);
    return EXIT_SUCCESS;
}