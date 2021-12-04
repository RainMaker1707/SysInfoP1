#include "../headers/philosophers.h"
#define ITERATIONS 100000

void eat(){
    // emulated eating with no delay
}

void think(){
    // emulated thinking with no delay
}

void *party(void* voidArg){
    param_t *args = (param_t*) voidArg;
    // syllabus code with no deadlock
    for(int i = 0; i < ITERATIONS; i++){
        int left = args->id;
        int right = (args->id+1) % args->N;
        think();
        if(left < right){
            pthread_mutex_lock(args->chopsticks + left);
            pthread_mutex_lock(args->chopsticks + right);
        }else{
            pthread_mutex_lock(args->chopsticks + right);
            pthread_mutex_lock(args->chopsticks + left);
        }
        eat();
        // if(i%10000 == 0) printf("id: %d, round: %d\n", args->id, i); // TODO rm debug line
        pthread_mutex_unlock(args->chopsticks + left);
        pthread_mutex_unlock(args->chopsticks + right);
    }
    // free of arguments
    free(args);
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("You must provide only one argument N number of philosophers\n");
        return EXIT_FAILURE;
    }
    if(argv[1]){
        // check if threads number is in the range [1, 64[
        int philosophers_number = (int)strtol(argv[1], &argv[2] - 1, 10);
        if(philosophers_number <= 1 || philosophers_number > 640) {
            printf("N must be positive integer greater than 1 and less than 64\n");
            return EXIT_FAILURE;
        }
        // definition of mutex and threads
        pthread_mutex_t chopsticks[philosophers_number];
        pthread_t thread[philosophers_number];

        // malloc all shared variables
        for (int i=0; i < philosophers_number; i++) pthread_mutex_init(&chopsticks[i], NULL);

        for(int i = 0; i < philosophers_number; i++){
            param_t *arg = (param_t*)malloc(sizeof(param_t));
            if(!arg) return EXIT_FAILURE;
            arg->id = i;
            arg->N = philosophers_number;
            arg->chopsticks = &chopsticks[0];
            pthread_create(&thread[i], NULL, party, (void*)arg);
        }

        // wait for all thread to end and then destroy the mutex
        for(int i = 0; i< philosophers_number; i++) pthread_join(thread[i], NULL);
        for(int i = 0; i< philosophers_number; i++) pthread_mutex_destroy(&chopsticks[i]);
    }
    return EXIT_SUCCESS;
}
