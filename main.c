#include <stdio.h>

void process_command(char *command_with_args);
char * readcommand();

int main() {
	int loop = 1;
	while (loop) {
		process_command(readcommand());
		loop = 0;
	}

	return 0;
}

void process_command(char *command_with_args) {
	printf("proccessing command %s\n", command_with_args);
	return;
}

char * readcommand() {
	printf("reading from STDIN\n");
	return "the command from STDIN";
}

