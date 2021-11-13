#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHILOSOPHERS 4
int maxEat = 100;
int minEat = 1;
pthread_t phil[PHILOSOPHERS];
pthread_mutex_t chopsticks[PHILOSOPHERS];

void eat(int id){
    int end  = rand() % (maxEat + 1 - minEat) + minEat;
    for(int i = 0; i < end ; i++){
        //printf("Philosophe %d mange\n", id);
    }
}

void * party(void* arg){
    int *id =(int*)arg;
    printf("Enter %d\n", *id);
    int left = *id;
    int right = (left + 1) % PHILOSOPHERS;
    int PART = 100;
    while(PART >= 0){
        //printf("Philosophe %d pense\n", *id);
        if(left < right) {
            pthread_mutex_lock(&chopsticks[left]);
            pthread_mutex_lock(&chopsticks[right]);
        }else{
            pthread_mutex_lock(&chopsticks[right]);
            pthread_mutex_lock(&chopsticks[left]);
        }
        eat(*id);
        printf("Philo %d leaves chopsticks \n", *id);
        pthread_mutex_unlock(&chopsticks[left]);
        pthread_mutex_unlock(&chopsticks[right]);
        usleep(100);
        PART-=1;
        printf("Part = %d\n", PART);
    }

    return NULL;
}


int main() {
    int *ids = (int*)malloc(sizeof(int)*PHILOSOPHERS); //malloc to share variables
    if(!ids)return EXIT_FAILURE;
    for(int i= 0; i<PHILOSOPHERS; i++) ids[i] = i;
    pthread_t *tab = (pthread_t*)malloc(sizeof(pthread_t)*PHILOSOPHERS);
    for(int i=0; i<PHILOSOPHERS; i++) pthread_create(&tab[i], NULL, party, (void*)&(ids[i]));
}
