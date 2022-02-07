#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[], char* envp[]) {
	int i = 0;
	for (; i < argc; ++i) {
		printf("argv - %s\n", argv[i]);
	}
	i = 0;
	while (envp[i]) {
		printf("envp - %s\n", envp[i]);
		i++;
	}
	return 0;
}