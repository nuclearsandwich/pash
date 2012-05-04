#include <stdlib.h>
#include <string.h>
#include "../include/tokenizer.h"

strlist *tokenize(char *input) {
	int i, tokpos, inputc, intoken;
	inputc = strlen(input);
	tokpos = intoken = 0;

	strlist *head = malloc(sizeof(strlist));
	strlist *token = head;
	strlist *tail = head;
	head->next = NULL;

	for (i = 0; i < inputc; i++) {
		if (input[i] == ' ') {
			if(intoken) {
				/* Terminate the token with a null byte. */
				token->str[tokpos] = '\0';
				/* Leave the current token and reset the position. */
				intoken = tokpos = 0;
				/* Append token to existing list. */
				tail->next = token;
				/* Make this token the new tail. */
				tail = token;
				tail->next = NULL;
				/* Allocate a new token. */
				token = malloc(sizeof(strlist));
			}
		} else {
			intoken = 1;
			token->str[tokpos] = input[i];
			tokpos++;
			// TODO Bounds check tokpos
		}
	}

	/* If we ended in a word, we need to close it. Otherwise we
	 * need to clean up the current token.
	 */
	if (intoken) {
		/* Terminate the token with a null byte. */
		token->str[tokpos] = '\0';
		/* Append token to existing list. */
		tail->next = token;
		/* Make this token the new tail. */
		tail = token;
		tail->next = NULL;
	} else {
		free(token);
	}

	return head;
}

