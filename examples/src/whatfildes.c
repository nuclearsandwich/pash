#include <stdio.h>
#include <stdlib.h>

int main() {
	int indes, outdes, errdes;
	indes = fileno(stdin);
	outdes = fileno(stdout);
	errdes = fileno(stderr);

	printf("File descriptor numbers stdin: %d; stdout: %d; stderr: %d\n",
			indes, outdes, errdes);
	return 0;
}
