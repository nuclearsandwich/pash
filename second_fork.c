#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int pid;
	pid = fork();
	if (pid < 0) {
		printf("Can't fork!!\n");
		exit(1);
	}

	if (pid == 0) {
		printf("I am the child and my pid is %d", pid);
	} else {
		printf("I am the parent and my pid is %d\n.", getpid());
	}
	return 0;
}
