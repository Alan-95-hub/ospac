#include <sys/types.h>
#include <unistd.h>
int main() {
	int pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("My ID - %d, Parent ID - %d\n", pid, ppid);
	return 0;
}