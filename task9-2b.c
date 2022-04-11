#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>

int main() {
    int* array;
    int shmid, semid, new = 1;
    long i;
    char pathname[] = "09-2a.c";
    key_t key;
    struct sembuf buf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error can\'t generate key\n");
        exit(-1);
    }
    if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Error can\'t create shared memory\n");
            exit(-1);
        }
        else {
            if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
                printf("Error can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }
    if ((array = (int*)shmat(shmid, NULL, 0)) == (int*)(-1)) {
        printf("Error can\'t attach shared memory\n");
        exit(-1);
    }
    if ((semid = semget(key, 1, 0666)) < 0) {
        if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
            printf("Error can\'t create semaphore set\n");
            exit(-1);
        }
        buf.sem_num = 0;
        buf.sem_op = 1;
        buf.sem_flg = 0;
        if (semop(semid, &buf, 1) < 0) {
            printf("Error can\'t wait for condition\n");
            exit(-1);
        }
    }
    if (new) {
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
        printf("OK\nprogram 1 - %d times, program 2 - %d times, all - %d times\n", array[0], array[1], array[2]);
    } else {
        buf.sem_num = 0;
        buf.sem_op = -1;
        buf.sem_flg = 0;
        if (semop(semid, &buf, 1) < 0) {
            printf("Error can\'t wait for condition\n");
            exit(-1);
        }
        array[1] += 1;
        for (i = 0; i < 2000000000L; i++);
        array[2] += 1;
        printf("OK\nprogram 1 - %d times, program 2 - %d times, all - %d times\n", array[0], array[1], array[2]);
        buf.sem_num = 0;
        buf.sem_op = 1;
        buf.sem_flg = 0;
        if (semop(semid, &buf, 1) < 0) {
            printf("Error can\'t wait for condition\n");
            exit(-1);
        }
    }
    if (shmdt(array) < 0) {
        printf("Error can\'t detach shared memory\n");
        exit(-1);
    }

    return 0;
}