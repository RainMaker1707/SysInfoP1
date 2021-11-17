#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

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
    printf("P: %d -- C: %d\n", *producer_number, *consumer_number);

    // free all malloced variables
    free(producer_number);
    free(consumer_number);
    return EXIT_SUCCESS;
}
