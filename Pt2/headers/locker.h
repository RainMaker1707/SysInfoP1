#ifndef SYSINFOP1_LOCKER_H
#define SYSINFOP1_LOCKER_H

typedef struct locker{
    int state;
}lock_t;

void lock_init(lock_t *mutex);
void lock(lock_t *mutex);
void unlock(lock_t *mutex);
void test_and_test_and_set_lock(lock_t *mutex);

#endif //SYSINFOP1_LOCKER_H
