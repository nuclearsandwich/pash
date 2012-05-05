#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"


ast_node *parse() {
	return parse_command_sequence();
}

ast_node *parse_command_sequence() {
	ast_node *command = malloc(sizeof(ast_node));
	command->type = COMMAND;
	strncpy(command->token, tokens->str, MAX_TOKEN_LENGTH);
	strip_head();
	command->children = parse_arglist();
	return command;
}

ast_nodelist *parse_arglist() {
	ast_nodelist *head, *tail;
	ast_node *arg_node;
	if (tokens == NULL) {
		return NULL;
	}
	/* Prep the first node */
	head = tail = malloc(sizeof(ast_nodelist));
	head->node = parse_arg();
	head->next = NULL;

	/* Prime the while with a new argument */
	arg_node = parse_arg();

	while (arg_node != NULL) {
		tail->next = malloc(sizeof(ast_nodelist));
		tail = tail->next;
		tail->node = arg_node;
		tail->next = NULL;
		arg_node = parse_arg();
	}
	return head;
}

ast_node *parse_arg() {
	if (tokens == NULL) {
		return NULL;
	}

	if (tokens->str[0] == '$') {
		return parse_variable();
	}

	return parse_value();
}

ast_node *parse_value() {
	ast_node *value = malloc(sizeof(ast_node));
	value->type = VALUE;
	strncpy(value->token, tokens->str, MAX_TOKEN_LENGTH);
	strip_head();
	return value;
}

ast_node *parse_variable() {
	int i, varlen = strlen(tokens->str);
	ast_node *variable = malloc(sizeof(ast_node));
	variable->type = VARIABLE;
	for (i = 0; i < varlen; i++) {
		variable->token[i] = tokens->str[i + 1];
	}
	strip_head();
	return variable;
}

void strip_head() {
	strlist *head = tokens;
	tokens = head->next;
	free(head);
}

