#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define ITERATIONS 10000

void eat(){
}

void think(){
}

void *party(void* args){
    int *id = (int*)&((char**)args)[0];
    int *philosophers_number = (int*)(((char**)args) + 4);
    pthread_mutex_t *chopsticks = (pthread_mutex_t*)(((char*)args) + 8);
    int left = *id;
    int right = (*id + 1) % *philosophers_number;
    for(int i=0; i < ITERATIONS; i++) {
        think();
        // lock chopsticks
        pthread_mutex_lock(&chopsticks[left]);
        pthread_mutex_lock(&chopsticks[right]);
        eat();
        // leave chopsticks
        pthread_mutex_unlock(&chopsticks[left]);
        pthread_mutex_unlock(&chopsticks[right]);
    }
    printf("id: %d, philo_n: %d\n", *id, *philosophers_number);
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("You must provide only one argument N number of philosophers");
        return EXIT_FAILURE;
    }
    if(argv[1]){
        int philosophers_number = (int)strtol(argv[1], &argv[2], 10);
        if(philosophers_number <= 0) {
            printf("N must be positive integer");
            return EXIT_FAILURE;
        }
        pthread_mutex_t *chopsticks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*philosophers_number);
        if(!chopsticks) return EXIT_FAILURE;
        for(int i = 0; i < philosophers_number; i++) pthread_mutex_init(&chopsticks[i], NULL);
        pthread_t *tab = (pthread_t*)malloc(sizeof(pthread_t)*philosophers_number);
        if(!tab) return EXIT_FAILURE;
        char* ads[4];
        for(int i = 0; i < philosophers_number; i++) {
            char **array = (char **) malloc(sizeof(int) * 2 + sizeof(pthread_mutex_t) * philosophers_number);
            if(!array) return EXIT_FAILURE;
            *(int*)&array[0] = i;
            *(int*)&array[4] = philosophers_number;
            array[8] = (char *) chopsticks;
            pthread_create(&tab[i], NULL, party, (void*)array);
            ads[i] = (void*)array;
        }
        sleep(1);
        printf("OK\n");
        for(int i = 0; i < philosophers_number; i++) {
            pthread_detach(tab[i]);
            pthread_mutex_destroy(&chopsticks[i]);
            free(ads[i]);
        }
        free(tab);
        free(chopsticks);
    }
    return EXIT_SUCCESS;
}
