#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHILOSOPHES 4
int PART=10000; // number of portion to eat
pthread_t phil[PHILOSOPHES];
pthread_mutex_t baguette[PHILOSOPHES];

void eat(int id){
    for(int i = 0; i < rand()%10; i++){
        printf("Philosophe %d mange\n", id);
        PART-=1;
    }
}

void * philo(void* arg){
    int *id =(int*)arg;
    printf("Enter %d\n", *id);
    int left = *id;
    int right = (left + 1) % PHILOSOPHES;
    while(PART >= 0){
        printf("Philosophe %d pense\n", *id);
        if(left < right){
            printf("Philo %d take baguette left\n", *id);
            pthread_mutex_lock(&baguette[left]);
            printf("Philo %d take baguette right\n", *id);
            pthread_mutex_lock(&baguette[right]);
        }else{
            printf("Philo %d take baguette right\n", *id);
            pthread_mutex_lock(&baguette[right]);
            printf("Philo %d take baguette left\n", *id);
            pthread_mutex_lock(&baguette[left]);
        }
        eat(*id);
        printf("Philo %d leaves baguette left\n", *id);
        pthread_mutex_unlock(&baguette[left]);
        printf("Philo %d leaves baguette right\n", *id);
        pthread_mutex_unlock(&baguette[right]);
    }
    return NULL;
}


int main() {
    int *ids = malloc(sizeof(int)*4); //malloc to share variables
    if(!ids)return EXIT_FAILURE;
    for(int i= 0; i<PHILOSOPHES; i++) ids[i] = i;
    pthread_t tab[PHILOSOPHES];
    for(int i=0; i<PHILOSOPHES; i++) pthread_create(&tab[i], NULL, philo, (void*)&(ids[i]));
}
