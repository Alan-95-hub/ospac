#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sendpid;
int number = 0b11111111111111111111111111111111;
int step = 0;

void zero() {
    number = number ^ (1 << step);
    step++;
    if (step == 32) {
        printf("get number: %d\n", number);
        exit(0);
    } else {
        printf("get %d bit: %d\n", step, 0);
        kill(sendpid, SIGUSR1);
    }
}

void one() {
    step++;
    if (step == 32) {
        printf("get number %d\n", number);
        exit(0);
    } else {
        printf("get %d bit: %d\n", step, 1);
        kill(sendpid, SIGUSR1);
    }
}

int main(void) {
    (void)signal(SIGUSR1, zero);
    (void)signal(SIGUSR2, one);
    printf("my PID: %d\n", getpid());
    printf("enter sender\'s PID: ");
    scanf("%d", &sendpid);
    while (true) {};
}