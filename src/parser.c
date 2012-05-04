#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

ast_node *parse(strlist *tokens) {
	return parse_command_sequence(tokens);
}

ast_node *parse_command_sequence(strlist *tokens) {
	ast_node *command = malloc(sizeof(ast_node));
	command->type = COMMAND;
	strncpy(command->token, tokens->str, MAX_TOKEN_LENGTH);
	command->children = parse_arglist(tokens->next);
	return command;
}

ast_nodelist *parse_arglist(strlist *tokens) {
	ast_nodelist *head, *tail;
	if (tokens == NULL) {
		return NULL;
	}

	head = tail = malloc(sizeof(ast_nodelist));
	while (tokens != NULL) {
		tail->next = malloc(sizeof(ast_nodelist));
		tail = tail->next;
		tail->next = NULL;
		tail->node.type = ARG;
		strncpy(tail->node.token, tokens->str, MAX_TOKEN_LENGTH);
		tokens = tokens->next;
	}

	return head;
}

