#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHILOSOPHES 4
int PART=10; // number of portion to eat
pthread_t phil[PHILOSOPHES];
pthread_mutex_t baguette[PHILOSOPHES];

void eat(int id){
    printf("Philosophe %d mange\n", id);
    sleep(1);
    printf("\n");
}

void * philo(void* arg){
    int *id =(int*) arg;
    printf("Enter %d\n", *id);
    int left = *id;
    int right = (left + 1) % PHILOSOPHES;
    while(true){
        PART -= 1;
        printf("Philosophe %d pense\n", *id);
        if(left < right){
            pthread_mutex_lock(&baguette[left]);
            pthread_mutex_lock(&baguette[right]);
        }else{
            pthread_mutex_lock(&baguette[right]);
            pthread_mutex_lock(&baguette[left]);
        }
        eat(*id);
        pthread_mutex_unlock(&baguette[left]);
        pthread_mutex_unlock(&baguette[right]);
        if(PART == 0) break;
    }
    return NULL;
}


int main() {
    int ids[] = {0, 1, 2, 3} ;
    for(int i=0; i<PHILOSOPHES; i++) {
        pthread_create(philo((void*)&(ids[i])), NULL, 0, NULL);
    }
}
