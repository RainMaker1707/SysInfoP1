#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHILOSOPHERS 4

pthread_t phil[PHILOSOPHERS];
pthread_mutex_t chopsticks[PHILOSOPHERS];

void eat(int id){
    int maxEat = 10000;
    int minEat = 1;
    int time  = rand() % (maxEat + 1 - minEat) + minEat;
    printf("Philosopher %d eat\n", id);
    int i = 0;
    while(i<time) i++;
}

void * party(void* arg){
    int *id =(int*)arg;
    int left = *id;
    int right = (left + 1) % PHILOSOPHERS;
    int PART = 10000;
    while(PART >= 0){
        printf("Philosopher %d thinks\n", *id);
        if(left < right) {
            pthread_mutex_lock(&chopsticks[left]);
            pthread_mutex_lock(&chopsticks[right]);
            printf("Philosopher %d locked chopsticks %d - %d\n", *id, left, right);
        }else{
            pthread_mutex_lock(&chopsticks[right]);
            pthread_mutex_lock(&chopsticks[left]);
            printf("Philosopher %d locked chopsticks %d - %d\n", *id, left, right);
        }
        eat(*id);
        pthread_mutex_unlock(&chopsticks[left]);
        pthread_mutex_unlock(&chopsticks[right]);
        printf("Philosopher %d left chopsticks %d - %d\n", *id, left, right);
        PART-=1;
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
