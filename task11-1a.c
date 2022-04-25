#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main() {
    int msqid, len;
    char pathname[] = "11-1a.c";
    key_t key;
    struct mymsgbuf {
        long mtype;
        struct {
            int int_info;
            float float_info;
        } info;
    } mybuf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error\n");
        exit(-1);
    }
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Error\n");
        exit(-1);
    }
    for (int i = 1; i <= 5; ++i) {
        mybuf.mtype = 1;
        mybuf.info.int_info = 123;
        mybuf.info.float_info = 1.23;
        len = sizeof(mybuf.info);
        if (msgsnd(msqid, &mybuf, len, 0) < 0) {
            printf("Error\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
            exit(-1);
        }
    }
    mybuf.mtype = LAST_MESSAGE;
    len = 0;
    if (msgsnd(msqid, &mybuf, len, 0) < 0) {
        printf("Error\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
        exit(-1);
    }
    return 0;
}