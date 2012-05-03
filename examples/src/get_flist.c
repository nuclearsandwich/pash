#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 256

int main() {

	pid_t ls_pid;
	int ls_status;
	int fd[2];
	char buf[BUFSIZE];
	FILE *ls_output;
	const char* fileext = ".sh142\n";

	if (pipe(fd) == -1) {
		fprintf(stderr, "Unable to create pipe!\n");
	}

	if ((ls_pid = fork()) == -1) {
		fprintf(stderr, "Cannot fork! Bailin' out.\n");
		exit(1);
	}
	
	if (!ls_pid) {

		/* Close the parent process's stdin, stdout, and stderr */
		close(fileno(stdin));
		close(fileno(stdout));
		close(fileno(stderr));

		/* Attach stdout of ls command to pipe writing to parent. */
		dup2(fd[1], fileno(stdout));

		/* Doesn't work since * only expands from witin shell. :( */
		execlp("ls", "ls", NULL);
	}

	else {
		/* Close the write file descriptor in the parent. */
		close(fd[1]);
		waitpid(ls_pid, &ls_status, 0);
		ls_output = fdopen(fd[0], "r");

		while(fgets(buf, BUFSIZE, ls_output) != NULL) {
			if (strstr(buf, fileext) != NULL) {
				printf("You win! %s\n", buf);
			}
		}
		printf("The exit status of ls was %d\n", WEXITSTATUS(ls_status));
	}

	return 0;
}

