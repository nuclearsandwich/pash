#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
	int pid, child_status;

	pid = fork();

	/* child */
	if (pid == 0) {
		execlp("whoami", "whoami", NULL);
	} else if (pid == wait(&child_status)) {
		printf("Return from child process %d was %d.\n", pid, child_status);
	} else {
		printf("Got wrong child.");
	}
	return 0;
}

