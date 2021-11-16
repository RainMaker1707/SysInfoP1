#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITERATIONS 10000

void eat(){
}

void think(){
}

void *party(void* voidArg){
    char** args = (char**)voidArg;
    int *id = (int*)args[0];
    int *N = (int*)args[1];
    pthread_mutex_t *chopsticks[*N];
    for(int i = 0; i < *N; i++){
        chopsticks[i] = (pthread_mutex_t *)args[2+i];
    }
    for(int i = 0; i < ITERATIONS; i++){
        int left = *id;
        int right = (*id+1) % *N;
        think();
        if(left < right){
            pthread_mutex_lock(chopsticks[left]);
            pthread_mutex_lock(chopsticks[right]);
        }else{
            pthread_mutex_lock(chopsticks[right]);
            pthread_mutex_lock(chopsticks[left]);
        }
        eat();
        pthread_mutex_unlock(chopsticks[left]);
        pthread_mutex_unlock(chopsticks[right]);
        pthread_yield_np();
    }
    free(args);
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("You must provide only one argument N number of philosophers\n");
        return EXIT_FAILURE;
    }
    if(argv[1]){
        int philosophers_number = (int)strtol(argv[1], &argv[2], 10);
        if(philosophers_number <= 1 || philosophers_number > 64) {
            printf("N must be positive integer greater than 1 and less than 64\n");
            return EXIT_FAILURE;
        }
        pthread_mutex_t chopsticks[philosophers_number];
        pthread_t thread[philosophers_number];
        int *pn = malloc(sizeof(int));
        if(!pn) return EXIT_FAILURE;
        int *ids = malloc((sizeof(int)*philosophers_number));
        if(!ids) return EXIT_FAILURE;
        *pn = philosophers_number;
        for (int i=0; i < philosophers_number; i++) {
            ids[i] = i;
            pthread_mutex_init(&chopsticks[i], NULL);
        }
        for(int i = 0; i < philosophers_number; i++){
            char **args = malloc(2 + philosophers_number);
            if(!args) return EXIT_FAILURE;
            args[0] = (char*)&ids[i];
            args[1] = (char*)pn;
            for(int j = 0; j < philosophers_number; j++) args[2+j] = (char*)&(chopsticks[j]);
            pthread_create(&thread[i], NULL, party, (void*)args);
        }
        for(int i = 0; i< philosophers_number; i++) pthread_join(thread[i], NULL);
        for(int i = 0; i< philosophers_number; i++) pthread_mutex_destroy(&chopsticks[i]);
        free(pn);
        free(ids);
    }
    return EXIT_SUCCESS;
}
