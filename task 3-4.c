#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[], char* envp[]) {
	pid_t pid = fork();
	if (pid < 0) {
		printf("Error\n");
	}
	else if (pid == 0) {
		printf("Child\n");
		(void)execle("/bin/cat", "/bin/cat", "task4-1.c", 0, envp);
		printf("Error\n");
	}
	else printf("Parent\n");
	pid_t ppid = getppid();
	printf("My pid = %d, my ppid = %d", (int)pid, (int)ppid);
	return 0;
}