#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int     fd;
    char    file[] = "aaa.fifo";
    (void)umask(0);
    if (mknod(file, S_IFIFO | 0666, 0) < 0) {
        printf("FIFO creating error\n");
        exit(-1);
    }
    if ((fd = open(file, O_WRONLY)) < 0) {
        printf("FIFO writing error\n");
        exit(-1);
    }
    size_t size = write(fd, "xxx", 3);
    if (size != 3) {
        printf("FIFO writing error\n");
        exit(-1);
    }
    if (close(fd) < 0) {
        printf("FIFO closing error\n");
        exit(-1);
    }
    return 0;
}