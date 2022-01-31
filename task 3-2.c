
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    pid_t pid, ppid;
    int a = 0;
    (void)fork();
    a = a + 1;
    pid = fork();
    if (pid == -1) {
        printf("Error, ");
    }
    else if (pid == 0) {
        printf("Child, ");
    }
    else {
        printf("Parent, ");
    }
    ppid = getppid();
    printf("My pid = %d, my ppid = %d", (int)pid, (int)ppid);
        return 0;
}