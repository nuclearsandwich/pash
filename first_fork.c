#include <stdio.h>
#include <unistd.h>

int main() {
	int return_value;

	printf("Forking process!\n");
	fork();
	printf("The process id is %d and the return value is %d.\n",
			getpid(), return_value);
	execl("/bin/ls", "ls", "-l", 0);
	printf("This line is not printed");
	return 0;
}
