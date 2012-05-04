#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

int main() {
	char *command = "echo";
	strlist *tokens = malloc(sizeof(strlist));
	strncpy(tokens->str, command, MAX_TOKEN_LENGTH);
	tokens->next =  malloc(sizeof(strlist));
	strncpy(tokens->next->str, "hello", MAX_TOKEN_LENGTH);
	tokens->next->next = NULL;

	ast_node *ast = parse(tokens);
	ast_nodelist *children = ast->children;

	printf("The node type is COMMAND %d\n", (ast->type == COMMAND));
	printf("The token is %s\n", ast->token);
	printf("The node has children %d.\n\n", children != NULL);
	while (children != NULL) {
		printf("The node type is ARG %d\n", (children->node.type == ARG));
		printf("The token is %s\n", children->node.token);
		children = children->next;
	}
	return 0;
}

