#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int msqid, len, maxlen;
    char pathname[] = "11-2a.c";
    key_t key;
    struct mymsgbuf {
        long mtype;
        struct {
            int int_info;
        }info;
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
        len = sizeof(mybuf.info);
        if (msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0) < 0) {
            printf("Error\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
            exit(-1);
        }
    }
    for (int i = 1; i <= 5; ++i) {
        maxlen = sizeof(mybuf.info);
        if (len = msgrcv(msqid, (struct msgbuf*)&mybuf, maxlen, 2, 0) < 0) {
            printf("Error\n");
            exit(-1);
        }

        printf("OK, type = %ld,\n int_info = %i\n", mybuf.mtype, mybuf.info.int_info);
    }
    msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
    return 0;
}