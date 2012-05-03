#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		printf("The environment variable %s's value is %s.\n", argv[i], getenv(argv[i]));
	}

	return 0;
}
