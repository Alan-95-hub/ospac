#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
    int semid;
    char pathname[] = "09-1a.c";
    key_t key;
    struct sembuf buf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error can\'t generate key\n");
        exit(-1);
    }
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Error can\'t create semaphore set\n");
        exit(-1);
    }
    buf.sem_num = 0;
    buf.sem_flg = 0;
    buf.sem_op = -5;
    if (semop(semid, &buf, 1) < 0) {
        printf("Error can\'t wait for condition\n");
        exit(-1);
    }
    printf("OK\n");
    return 0;
}