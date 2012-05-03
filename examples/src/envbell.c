#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BELL_ENV "BELL"
#define OVERWRITE 1

int main(int argc, char *argv[]) {
	char *play_bell;
	const char *truth = "TRUE";

	play_bell = getenv(BELL_ENV);


	if (1) {
		printf("THE BELL TOLLS!\a FOR %s\n", getenv("USER"));
		printf("BELL ENV is %s\n", play_bell);
		setenv(BELL_ENV, "BELL PLAYED!", OVERWRITE);
		printf("BELL ENV is %s\n", getenv(BELL_ENV));
	}

	return 0;
}