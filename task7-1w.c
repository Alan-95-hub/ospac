#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    char* buffer;
    int current = 0;
    int id;
    char pathname[] = "07-1a.c";
    key_t key;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error generate\n");
        exit(-1);
    }
    if ((id = shmget(key, 2000 * sizeof(char), 0666 | IPC_CREAT)) < 0) {
        printf("Error memory\n");
        exit(-1);
    }
    if ((buffer = (char*)shmat(id, NULL, 0)) == (char*)(-1)) {
        printf("Error memory\n");
    }
    while (buffer[current] != '\0') {
        printf("%c", buffer[current]);
        current++;
    }
    if (shmdt(buffer) < 0) {
        printf("Error memory\n");
        exit(-1);
    }
    if (shmctl(id, 0, NULL) < 0) {
        printf("Error memory\n");
        exit(-1);
    }
    return 0;
}