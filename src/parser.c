#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

ast_node *parse() {
	int eql;
	ast_node *root;
	if ((eql = contains_eql(tokens->str)) != -1) {
		root =  parse_var_assign(eql);
	} else {
		root = parse_command();
	}
	return root;
}

ast_node *parse_command() {
	ast_node *command = malloc(sizeof(ast_node));
	command->type = COMMAND;
	strncpy(command->token, tokens->str, MAX_TOKEN_LENGTH);
	strip_head();
	command->children = malloc(sizeof(ast_nodelist));
	command->children->node = parse_arg_list();
	return command;
}

ast_node *parse_arg_list() {
	ast_node *arg_list = malloc(sizeof(ast_node)), *arg_node;
	ast_nodelist *head, *tail;
	head = tail = malloc(sizeof(ast_nodelist));
	arg_list->children = head;
	arg_node = parse_arg();
	tail->node = arg_node;
	strip_head();

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
	return arg_list;
}

ast_node *parse_arg() {
	if (tokens == NULL || is_special_token()) {
		return NULL;
	}

	if (tokens->str[0] == '$') {
		return parse_variable_expression();
	}

	return parse_value();
}

ast_node *parse_value() {
	ast_node *value = malloc(sizeof(ast_node));
	value->type = VALUE;
	strncpy(value->token, tokens->str, MAX_TOKEN_LENGTH);
	return value;
}

ast_node *parse_variable_expression() {
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

int is_special_token() {
	if (strcmp(tokens->str, "&&") == 0) {
		return 1;
	} else if (strcmp(tokens->str, "||") == 0) {
		return 1;
	} else {
		return 0;
	}
}


