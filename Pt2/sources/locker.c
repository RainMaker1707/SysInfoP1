#include "../headers/locker.h"

void lock_init(lock_t *mutex){
    mutex->state = 0;
}

void lock(lock_t *mutex){
    asm(    "REPEAT: movl $1, %%eax;" // define loop and move vlaue 1 in eax
            "xchgl %%eax, %0;" // exchange eax and mutex->state
            "testl %%eax, %%eax;" // make a condition test
            "jnz REPEAT;" // loop order
            :"=m"(mutex->state)
            :"m"(mutex->state) //asign mutex state to 1
            :"%eax" // clean eax
            );
}

void unlock(lock_t *mutex){
    asm(    "movl $0, %%eax;" //move value 0 in eax
            "xchgl %%eax, %0;" // exchange eax value and mutex->state
            :"=m"(mutex->state)
            :"m"(mutex->state) //asign mutex state to 0
            :"%eax" // clean eax
            );
}

void test_and_test_and_set_lock(lock_t *mutex){
    int eax_val; // register value
    while(true){
        asm(    "movl $1, %%eax;" //move value one in eax
                "xchgl %%eax, %1;" // exchange value eax and mutex->state
                "movl %%eax, %0;" // move eax value in eax_val
                :"=m"(eax_val)
                :"m"(mutex->state)
                :"%eax" // clean eax
                );
        if(eax_val == 0) break; // if eax_val is 0 old(mutex->state) was 1 then we locked it.
        while(mutex->state == 1); // waiting for state == 0
    }
}
