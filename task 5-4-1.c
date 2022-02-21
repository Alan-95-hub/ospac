#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd;
    char resstring[14];
    if ((fd = open("aaa.fifo", O_RDONLY)) < 0) {
        printf("FIFO reading error\n");
        exit(-1);
    }
    size_t size = read(fd, resstring, 14);
    if (size < 0) {
        printf("FIFO reading error\n");
        exit(-1);
    }
    printf(resstring);
    if (close(fd) < 0) {
        printf("FIFO closing error\n");
        exit(-1);
    }
    return 0;
}