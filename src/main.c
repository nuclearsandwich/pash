#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

/* The prompt string printed by Readline */
#define PROMPT_STRING "sh142$ "


int main() {
	char *input;
	int i;

	/* Set up exit status FIFO. */

	exitstatus_head = malloc(sizeof(int));
	*exitstatus_head = 0;
	for (i = 0; i < MAX_SAVED_EXITSTATUSES; i++) {
		exitstatuses[i] = UNSET_STATUS;
	}
	while(1) {
		input = readline(PROMPT_STRING);
		/* Break out when the user exits. */
		if (input == NULL || strcmp(input, "exit") == 0) {
			exit(0);
		}
		tokens = tokenize(input);
		interpret(parse());
	}
	return 0;
}

