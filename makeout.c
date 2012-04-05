#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

	int i;
	char* outfile = "";
	if (argc >= 2) {
		outfile = argv[1];
	}

	if (strcmp(outfile, "err") == 0) {
		for (i = 2; i < argc; i++) {
			fprintf(stderr, "%s ", argv[i]);
		}
		fprintf(stderr, "\n");
	} else if (strcmp(outfile, "out") == 0) {
	
		for (i = 2; i < argc; i++) {
			fprintf(stdout, "%s ", argv[i]);
		}
		fprintf(stdout, "\n");
	}

	return 0;
}

