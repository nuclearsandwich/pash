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
	while(1) {
		input = readline(PROMPT_STRING);
		/* Break out when the user exits. */
		if (input == NULL || strcmp(input, "exit") == 0) {
			exit(0);
		}
		interpret(parse(tokenize(input)));
	}
	return 0;
}

