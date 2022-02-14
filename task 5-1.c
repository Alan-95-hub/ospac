#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int     fd;
    char    restring[14];
    (void)umask(0);
    if ((fd = open("myfile", O_RDONLY, 0666)) < 0) {
        printf("Файл нельзя открыть\n");
        exit(-1);
    }
    size_t line = read(fd, restring, 14);
    if (line != 14) {
        printf("Нельзя прочитать\n");
        exit(-1);
    }
    printf("Значения в файле: %s\n", restring);
    if (close(fd) < 0) {
        printf("Нельзя закрыть файл\n");
    }
    return 0;
}