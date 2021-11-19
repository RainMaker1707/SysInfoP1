#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 8

void *producer(void* voidArg){
    usleep(10);
    char** args = (char**)voidArg;
    int *producer_number = (int*)args[0];
    printf("%d\n", *producer_number);
    return NULL;
}

void *consumer(void* voidArg){
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("You have to pass two arguments at the program.\n First one is the number of producers (int)\n Second one is number of consumers (int)\n");
        return EXIT_FAILURE;
    }
    // malloc of all shared variables
    int *producer_number = (int*)malloc(sizeof(int));
    if(!producer_number) return EXIT_FAILURE;
    int *consumer_number = (int*)malloc(sizeof(int));
    if(!consumer_number) return EXIT_FAILURE;
    // forced to convert the last one first because the endptr of strtol consume it.
    // to avoid this consummation we can reduce the address by one and then don't
    // the next argument
    *producer_number = (int)strtol(argv[1], &argv[2] - 1, 10);
    *consumer_number = (int)strtol(argv[2], &argv[3] - 1, 10);
    printf("P: %d -- C: %d\n", *producer_number, *consumer_number);// TODO rm

    // semaphore and mutexes + init mutexes
    sem_t empty, full;
    pthread_mutex_t buffer_m, producer_m, consumer_m;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&buffer_m, NULL);
    pthread_mutex_init(&producer_m, NULL);
    pthread_mutex_init(&consumer_m, NULL);

    // definition of the shared variables remaining
    int buffer[SIZE];
    int *producer_index = malloc(sizeof(int));
    if(!producer_index) return EXIT_FAILURE;
    int *consumer_index = malloc(sizeof(int));
    if(!consumer_index) return EXIT_FAILURE;
    *producer_index = 0, *consumer_index = 0;
    int *produced = malloc(sizeof(int));
    if(!produced) return EXIT_FAILURE;
    int *consumed = malloc(sizeof(int));
    if(!consumed) return EXIT_FAILURE;
    *produced = 0, *consumed = 0;

    // threads
    pthread_t consumers[*consumer_number];
    pthread_t producers[*producer_number];

    char** prod_args = malloc(8);
    prod_args[0] = (char*)producer_number;
    prod_args[1] = (char*)produced;
    prod_args[2] = (char*)&producer_m;
    prod_args[3] = (char*)&buffer_m;
    prod_args[4] = (char*)&buffer;
    prod_args[5] = (char*)&empty;
    prod_args[6] = (char*)&full;
    prod_args[7] = (char*)producer_index;
    for(int i = 0; i < *producer_number; i++){
        pthread_create(&producers[i], NULL, &producer, (void*)prod_args);
    }

    char** cons_args = malloc(8);
    cons_args[0] = (char*)&consumer_number;
    cons_args[1] = (char*)&consumed;
    cons_args[2] = (char*)&consumer_m;
    cons_args[3] = (char*)&buffer_m;
    cons_args[4] = (char*)&buffer;
    cons_args[5] = (char*)&empty;
    cons_args[6] = (char*)&full;
    cons_args[7] = (char*)&consumer_index;
    for(int i = 0; i < *consumer_number; i++){
        pthread_create(&consumers[i], NULL, &consumer, (void*)cons_args);
    }

    // wait for all threads end
    for(int i = 0; i < *consumer_number; i++){
        pthread_join(producers[i], NULL);
    }

    for(int i = 0; i < *consumer_number; i++){
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&buffer_m);
    pthread_mutex_destroy(&producer_m);
    pthread_mutex_destroy(&consumer_m);
    sem_destroy(&empty);
    sem_destroy(&full);
    // free all malloced variables
    free(producer_number);
    free(consumer_number);
    free(consumer_index);
    free(producer_index);
    free(produced);
    free(consumed);
    free(cons_args);
    free(prod_args);
    return EXIT_SUCCESS;
}
