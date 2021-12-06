#include "../headers/customBuffer.h"
#define SIZE 8
#define TOTAL 1024

void *producer(void* voidArg){
    int elem;
    param_t *arg = (param_t*) voidArg;
    while(true){
        while(rand() > RAND_MAX/10000);  // producer work simulation

        test_and_test_and_set_lock(arg->mutex_pc);
            if(*arg->counter >= TOTAL){
                unlock(arg->mutex_pc);
                return NULL; // stop when total is reached
            }
            *arg->counter+=1;
        unlock(arg->mutex_pc);

        elem = rand();// elem to add did it here to avoid rand() work int the sem lock

        sem_wait_(arg->free_p);  // producer waiting for a free place
        //printf("P: %d, ", *arg->counter);
            test_and_test_and_set_lock(arg->mutex_buf);
                *(arg->buffer  + *arg->index) = elem;
                *arg->index = (*arg->index+1) % SIZE;  // index update for next insertion
            unlock(arg->mutex_buf);
        sem_post_(arg->new_elem_sig); // signal new elem
    }
}
void *consumer(void* voidArg){
    param_t *arg = (param_t*) voidArg;
    int elem = 0;
    while(true){
        test_and_test_and_set_lock(arg->mutex_pc);
            if(*arg->counter >= TOTAL){
                unlock(arg->mutex_pc);
                return NULL; // stop when total is reach
            }
            *arg->counter += 1;
        unlock(arg->mutex_pc);

        sem_wait_(arg->new_elem_sig); // for elem to read
            test_and_test_and_set_lock(arg->mutex_buf);
                //printf("C: %d, ", *arg->counter);
                *(arg->buffer + *arg->index) = elem;
                *arg->index =  (*arg->index+1) % SIZE; // index update for next consummation
            unlock(arg->mutex_buf);
        sem_post_(arg->free_p);  // signal free place

        while(rand() > RAND_MAX/10000); //consumer work simulation
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("You have to pass two arguments at the program.\n First one is the number of producers (int)\n Second one is number of consumers (int)\n");
        return EXIT_FAILURE;
    }
    srand(time(NULL));
    // shared variables
    int buffer[SIZE];
    int producer_number = (int)strtol(argv[1], &argv[2] - 1, 10);
    int consumer_number = (int)strtol(argv[2], &argv[3] - 1, 10);
    int produced, consumed, cons_index, prod_index;
    produced = consumed = prod_index = cons_index = 0;
    // semaphore and mutexes + init mutexes
    sem_t2 *free_p = (sem_t2*)malloc(sizeof(sem_t2));
    sem_t2 *elem_sig = (sem_t2*)malloc(sizeof(sem_t2));
    lock_t *buffer_m = (lock_t*)malloc(sizeof(lock_t));
    lock_t *producer_m = (lock_t*)malloc(sizeof(lock_t));
    lock_t *consumer_m = (lock_t*)malloc(sizeof(lock_t));
    if(!(free_p && elem_sig && buffer_m && producer_m && consumer_m)) return EXIT_FAILURE;
    sem_init_(free_p, SIZE);
    sem_init_(elem_sig, 0);
    lock_init(buffer_m);
    lock_init(producer_m);
    lock_init(consumer_m);

    // threads
    pthread_t consumers[consumer_number];
    pthread_t producers[producer_number];

    // init producer param and threads
    param_t *prod_param = malloc(sizeof(param_t));
    if(!prod_param) return EXIT_FAILURE;
    prod_param->buffer = &buffer[0];
    prod_param->counter = &produced;
    prod_param->index = &prod_index;
    prod_param->free_p = free_p;
    prod_param->new_elem_sig = elem_sig;
    prod_param->mutex_buf = buffer_m;
    prod_param->mutex_pc = producer_m;
    for(int i = 0; i < producer_number; i++) pthread_create(&producers[i], NULL, &producer, (void*)prod_param);

    // init consumer param and threads
    param_t *cons_param = malloc(sizeof(param_t));
    if(!cons_param) return EXIT_FAILURE;
    cons_param->buffer = &buffer[0];
    cons_param->counter = &consumed;
    cons_param->index = &cons_index;
    cons_param->free_p = free_p;
    cons_param->new_elem_sig = elem_sig;
    cons_param->mutex_buf = buffer_m;
    cons_param->mutex_pc = consumer_m;
    for(int i = 0; i < consumer_number; i++) pthread_create(&consumers[i], NULL, &consumer, (void*)cons_param);
    // wait for all threads end
    for(int i = 0; i < producer_number; i++) pthread_join(producers[i], NULL);
    for(int i = 0; i < consumer_number; i++) pthread_join(consumers[i], NULL);
# ifdef DEBUG
    printf("prod: %d, cons %d", *prod_param->counter, *cons_param->counter);
# endif
    // garbage collect
    free(buffer_m);
    free(producer_m);
    free(consumer_m);
    free(prod_param);
    free(cons_param);
    return EXIT_SUCCESS;
}


