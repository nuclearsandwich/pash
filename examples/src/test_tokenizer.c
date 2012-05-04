#include <stdio.h>
#include <stdlib.h>
#include "../../include/tokenizer.h"

int main() {
	char *input = "The rain in spain falls mainly on the plain";

	int count = 0;
	strlist *tokens = tokenize(input);
	strlist *token = tokens;

	while(token != NULL) {
		printf("The %dth token is '%s'\n", count, token->str);
		count++;
		token = token->next;
	}
	return 0;
}
