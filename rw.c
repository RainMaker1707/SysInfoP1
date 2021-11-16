#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


void reader(void* voidArg){
}

void writer(void* voidArg){
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("You have to pass two arguments at the program.\n First one is writer thread number (int)\n Second one is reader threads number (int)\n");
        return EXIT_FAILURE;
    }
    int *reader_number = (int*)malloc(sizeof(int));
    if(!reader_number) return EXIT_FAILURE;
    int *writer_number = (int*)malloc(sizeof(int));
    if(!writer_number) return EXIT_FAILURE;
    int *reader_access = (int*)malloc(sizeof(int));
    if(!reader_access) return EXIT_FAILURE;
    int *writer_access = (int*)malloc(sizeof(int));
    if(!writer_access) return EXIT_FAILURE;
    *reader_number = (int)strtol(argv[2], &argv[3], 10);
    *writer_number = (int)strtol(argv[1], &argv[2], 10);
    *reader_access = 0;
    *writer_access = 0;
    printf("R: %d -- W: %d\n", *reader_number, *writer_number);
    return EXIT_SUCCESS;
}