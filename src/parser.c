#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"


ast_node *parse() {
	int eql;
	if ((eql = contains_eql(tokens->str)) != -1) {
		return parse_var_assign(eql);
	} else {
		return parse_command();
	}
}

ast_node *parse_command() {
	ast_node *command = malloc(sizeof(ast_node));
	command->type = COMMAND;
	strncpy(command->token, tokens->str, MAX_TOKEN_LENGTH);
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
	strip_head();
	head->next = NULL;

	/* Prime the while with a new argument */
	arg_node = parse_arg();
	strip_head();

	while (arg_node != NULL) {
		tail->next = malloc(sizeof(ast_nodelist));
		tail = tail->next;
		tail->node = arg_node;
		tail->next = NULL;
		arg_node = parse_arg();
		strip_head();
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
	return value;
}

ast_node *parse_variable() {
	int i, varlen = strlen(tokens->str);
	ast_node *variable = malloc(sizeof(ast_node));
	variable->type = VARIABLE;
	for (i = 0; i < varlen; i++) {
		variable->token[i] = tokens->str[i + 1];
	}
	return variable;
}

ast_node *parse_var_assign(int eqlidx) {
	ast_node *var_assign = malloc(sizeof(ast_node));
	ast_nodelist *varname = malloc(sizeof(ast_nodelist));
	ast_nodelist *value = malloc(sizeof(ast_nodelist));
	var_assign->type = VARASSIGN;
	var_assign->token[0] = '\0';
	tokens->str[eqlidx] = '\0';
	varname->node = parse_value();
	strncpy(tokens->str, &tokens->str[eqlidx + 1], MAX_TOKEN_LENGTH - eqlidx);
	value->node = parse_value();
	varname->next = value;
	var_assign->children = varname;
	return var_assign;
}

/* Helper Functions */
void strip_head() {
	if (tokens == NULL) {
		return;
	}
	strlist *head = tokens;
	tokens = head->next;
	free(head);
}

int contains_eql(char *str) {
	int i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '=') {
			return i;
		}
	}

	return -1;
}

