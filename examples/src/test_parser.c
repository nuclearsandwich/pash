#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

int main() {
	char *command = "echo";
	strlist *tokens = malloc(sizeof(strlist));
	strncpy(tokens->str, command, 64);
	tokens->next = NULL;

	ast_node *ast = parse(tokens);
	printf("The node type is COMMAND %d\n", (ast->type == COMMAND));
	printf("The token is %s\n", ast->token);
	return 0;
}

