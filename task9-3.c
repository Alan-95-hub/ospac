#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main() {
    int fd[2], result;
    size_t size;
    char  message[16];
    char pathname[] = "09-3.c";
    key_t key;
    struct sembuf mybuf;
    int semid;
    int N;
    scanf("%d", &N);
    if (pipe(fd) < 0) {
        printf("Error\n");
        exit(-1);
    }
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error\n");
        exit(-1);
    }
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Errort\n");
        exit(-1);
    }
    result = fork();
    if (result < 0) {
        printf("Error\n");
        exit(-1);
    }
    for (int i = 0; i < N; ++i) {
        if (result > 0) {
            size = write(fd[1], "Hi from parent!", 16);
            if (size != 16) {
                printf("Error\n");
                exit(-1);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = 2;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Error\n");
                exit(-1);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = 0;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Error parent\n");
                exit(-1);
            }
            size = read(fd[0], message, 16);
            if (size != 16) {
                printf("Error parent\n");
                exit(-1);
            }
            printf("ok\n");
        } else {
            mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Error parent\n");
                exit(-1);
            }
            size = read(fd[0], message, 16);
            if (size != 16) {
                printf("Error child\n");
                exit(-1);
            }
            printf("ok\n");
            size = write(fd[1], "Hi from chiild!", 16);
            if (size != 16) {
                printf("Error child\n");
                exit(-1);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Error parent\n");
                exit(-1);
            }
        }
    }
    if (close(fd[0]) < 0) {
        printf("Reading error\n"); exit(-1);
    }
    if (close(fd[1]) < 0) {
        printf("Writng error\n"); exit(-1);
    }
    return 0;
}