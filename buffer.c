#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 8

typedef struct param{
    int *number, *index, *counter;
    int *buffer;
    sem_t *empty, *full;
    pthread_mutex_t *mutex_buf, *mutex_pc;
}param_t;

void *producer(void* voidArg){
    //TODO
    param_t *arg = (param_t*) voidArg;
    printf("Number: %d, Counter: %d, \n", *arg->number, *arg->counter);
    return NULL;
}

void *consumer(void* voidArg){
    //TODO
    param_t *arg = (param_t*) voidArg;
    pthread_mutex_lock(arg->mutex_pc);
    *arg->counter = *arg->counter+1;
    printf("Number: %d, Counter: %d, \n", *arg->number, *arg->counter);
    pthread_mutex_unlock(arg->mutex_pc);
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("You have to pass two arguments at the program.\n First one is the number of producers (int)\n Second one is number of consumers (int)\n");
        return EXIT_FAILURE;
    }

    // shared variables
    int buffer[SIZE];
    int producer_number = (int)strtol(argv[1], &argv[2] - 1, 10);
    int consumer_number = (int)strtol(argv[2], &argv[3] - 1, 10);
    int produced, consumed, cons_index, prod_index = 0;
    printf("P: %d -- C: %d\n", producer_number, consumer_number);// TODO rm

    // semaphore and mutexes + init mutexes
    sem_t empty, full;
    pthread_mutex_t buffer_m, producer_m, consumer_m;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&buffer_m, NULL);
    pthread_mutex_init(&producer_m, NULL);
    pthread_mutex_init(&consumer_m, NULL);

    // threads
    pthread_t consumers[consumer_number];
    pthread_t producers[producer_number];

    // init producer param and threads
    param_t *prod_param = malloc(sizeof(param_t));
    if(!prod_param) return EXIT_FAILURE;
    prod_param->buffer = &buffer[0];
    prod_param->number = &producer_number;
    prod_param->counter = &produced;
    prod_param->index = &prod_index;
    prod_param->empty = &empty;
    prod_param->full = &full;
    prod_param->mutex_buf = &buffer_m;
    prod_param->mutex_pc = &producer_m;
    for(int i = 0; i < producer_number; i++){
        pthread_create(&producers[i], NULL, &producer, (void*)prod_param);
    }

    // init consumer param and threads
    param_t *cons_param = malloc(sizeof(param_t));
    if(!cons_param) return EXIT_FAILURE;
    cons_param->buffer = &buffer[0];
    cons_param->number = &consumer_number;
    cons_param->counter = &consumed;
    cons_param->index = &cons_index;
    cons_param->empty = &empty;
    cons_param->full = &full;
    cons_param->mutex_buf = &buffer_m;
    cons_param->mutex_pc = &consumer_m;
    for(int i = 0; i < consumer_number; i++){
        pthread_create(&consumers[i], NULL, &consumer, (void*)cons_param);
    }

    // wait for all threads end
    for(int i = 0; i < producer_number; i++) pthread_join(producers[i], NULL);
    for(int i = 0; i < consumer_number; i++) pthread_join(consumers[i], NULL);

    // garbage
    pthread_mutex_destroy(&buffer_m);
    pthread_mutex_destroy(&producer_m);
    pthread_mutex_destroy(&consumer_m);
    sem_destroy(&empty);
    sem_destroy(&full);
    // free all malloced variables
    free(prod_param);
    free(cons_param);
    return EXIT_SUCCESS;
}
