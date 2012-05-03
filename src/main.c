#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_runner.h"
#include "input_reader.h"

#define PROMPT_STRING "sh142$ "

void process_command(char *command_with_args);

int main() {
	char *input;
	while(1) {
		input = readline(PROMPT_STRING);
		/* Break out when the user exits. */
		if (input == NULL || strcmp(input, "exit") == 0) {
			exit(0);
		}
		process_command(input);
	}

	return 0;
}

void process_command(char *command_with_args) {
	system(command_with_args);
}

