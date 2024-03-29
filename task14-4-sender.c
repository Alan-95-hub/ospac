﻿#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int received = 1;
void wait() {
    received = 1;
}

int main(void) {
    (void)signal(SIGUSR1, wait);
    printf("my PID: %d\n", getpid());
    int recpid;
    printf("enter receiver\'s PID: ");
    scanf("%d", &recpid);
    int number;
    printf("enter number: ");
    scanf("%d", &number);
    for (int i = 0; i < 32; ++i) {
        if ((number & (1 << i)) == 0) {
            kill(recpid, SIGUSR1);
        } else {
            kill(recpid, SIGUSR2);
        }
        received = 0;
        while (i != 31 && received == 0) {}
    }
    printf("send number: %d\n", number);
    return 0;
}