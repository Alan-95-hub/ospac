#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd1[2], fd2[2];
    size_t line1, line2;
    char  resstring1[21], resstring2[20];
    if (pipe(fd1) < 0) {
        printf("Нельзя открыть первый файл\n");
        exit(-1);
    }
    if (pipe(fd2) < 0) {
        printf("Нельзя открыть второй файл\n");
        exit(-1);
    }
    int result = fork();
    if (result < 0) {
        printf("Нельзя соединиться с ребенком\n");
        exit(-1);
    }
    else {
        if (result > 0) {
            if (close(fd1[0]) < 0) {
                printf("Родитель, нельзя закрыть с первого файла\n"); exit(-1);
            }
            line1 = write(fd1[1], "Привет, это родитель!", 21);
            if (line1 != 21) {
                printf("Нельзя записать все в первый файл\n");
                exit(-1);
            }
            if (close(fd1[1]) < 0) {
                printf("Родитель, нельзя написать с первого файла\n"); exit(-1);
            }
            if (close(fd2[1]) < 0) {
                printf("Родитель, нельзя написать со второго файла\n"); exit(-1);
            }
            line2 = read(fd2[0], resstring2, 20);
            if (line2 < 0) {
                printf("Нельзя прочитать со второго файла\n");
                exit(-1);
            }
            printf("Родитель:  %s\n", resstring2);
            if (close(fd2[0]) < 0) {
                printf("Родтель, нельзя прочитать с первого файла\n"); exit(-1);
            }
        } else {
            if (close(fd1[1]) < 0) {
                printf("Ребенок, нельзя записать в первый файл\n"); exit(-1);
            }
            line1 = read(fd1[0], resstring1, 21);
            if (line1 < 0) {
                printf("Нельзя прочитать\n");
                exit(-1);
            }
            printf("Ребенок:  %s\n", resstring1);
            if (close(fd1[0]) < 0) {
                printf("Ребенок, нельзя прочитать с первого файла\n"); exit(-1);
            }
            if (close(fd2[0]) < 0) {
                printf("Ребенок, нельзя прочитать со второго файла\n"); exit(-1);
            }
            line2 = write(fd2[1], "Привет, это ребенок!", 20);
            if (line2 != 20) {
                printf("Нельзя записать все во второй файл\n");
                exit(-1);
            }
            if (close(fd2[1]) < 0) {
                printf("Ребенок, нельзя записать все во второй файл\n"); exit(-1);
            }
        }
    }
    return 0;
}