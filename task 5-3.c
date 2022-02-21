#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd[2], full = 0;
    if (pipe2(fd, O_NONBLOCK) < 0) {
        printf("Error\n");
        exit(-1);
    }
    int result = 0;
    while (!full) {
        if (write(fd[1], "p", 1) > 0) {
            result++;
        } else {
            full = 1;
        }
    }
    printf(result);
    if (close(fd[0]) < 0) {
        printf("Reading error\n"); exit(-1);
    }
    if (close(fd[1]) < 0) {
        printf("Writng error\n"); exit(-1);
    }
    return 0;
}