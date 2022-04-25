#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main() {
    int msqid, len, maxlen;
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
    while (1) {
        maxlen = sizeof(mybuf.info);
        if (len = msgrcv(msqid, &mybuf, maxlen, 0, 0) < 0) {
            printf("Error\n");
            exit(-1);
        }
        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, NULL);
            exit(0);
        }
        printf("OK, type = %ld,\n int_info = %i,\n float_info = %f\n", mybuf.mtype, mybuf.info.int_info, mybuf.info.float_info);
    }
    return 0;
}