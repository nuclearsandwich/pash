#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include "command_runner.h"

/* The prompt string printed by Readline */
#define PROMPT_STRING "sh142$ "
/* The maximum number of tokens per input line */
#define MAXTOKENS 64
#define MAXTOKLEN 32

void parsecommand(int tokenc, char *tokens[], char* input);
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

