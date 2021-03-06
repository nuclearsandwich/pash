#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/parser.h"

ast_node *parse() {
	int eql, colon;
	ast_node *root;
	if ((eql = contains_eql(tokens->str)) != -1) {
		root =  parse_var_assign(eql);
	} else if ((colon = contains_colon(tokens->str)) != -1) {
		root = parse_network_command(colon);
	} else if (is_negation(tokens->str)) {
		root = parse_negated_command();
	} else {
		root = parse_command();
	}
	return root;
}

/* Copy the current token as the name/path to the command to be run.
 * Then check if there are any regular tokens to accept as arguments. */
ast_node *parse_command() {
	ast_node *command = malloc(sizeof(ast_node));
	ast_nodelist *tail_child = NULL;
	command->type = COMMAND;
	strncpy(command->token, tokens->str, MAX_TOKEN_LENGTH);
	strip_head();

	/* Build ArgList if any. */
	if (tokens != NULL && !is_special_token()) {
		command->children = malloc(sizeof(ast_nodelist));
		command->children->node = parse_arg_list();
		command->children->next = NULL;
		/* Set the last child for appending redirects or chains. */
		tail_child = command->children;
	}

	/* Build RedirectList if any. */
	if (tokens != NULL && is_redirect_token()) {
		if (command->children == NULL) {
			command->children = malloc(sizeof(ast_nodelist));
			command->children->node = parse_redirect_list();
			command->children->next = NULL;
		} else {
			tail_child->next = malloc(sizeof(ast_nodelist));
			tail_child = tail_child->next;
			tail_child->node = parse_redirect_list();
			tail_child->next = NULL;
		}
	}

	/* Check for Background Key. */
	if (tokens != NULL && is_background_key()) {
		if (command->children == NULL) {
			tail_child = command->children = malloc(sizeof(ast_nodelist));
		} else {
			tail_child->next = malloc(sizeof(ast_nodelist));
			tail_child = tail_child->next;
		}
			tail_child->node = parse_background_key();
			tail_child->next = NULL;
	}

	return command;
}

ast_node *parse_arg_list() {
	ast_node *arg_list = malloc(sizeof(ast_node)), *arg_node;
	ast_nodelist *head, *tail;
	head = tail = malloc(sizeof(ast_nodelist));
	arg_list->type = ARGLIST;
	arg_list->children = head;
	arg_node = parse_arg();
	tail->node = arg_node;
	tail->next = NULL;

	if (arg_node != NULL) {
		strip_head();
	}

	arg_node = parse_arg();
	if (arg_node != NULL) {
		strip_head();
	}

	while (arg_node != NULL) {
		tail->next = malloc(sizeof(ast_nodelist));
		tail = tail->next;
		tail->node = arg_node;
		tail->next = NULL;
		arg_node = parse_arg();
		if (arg_node != NULL) {
			strip_head();
		}
	}
	return arg_list;
}

ast_node *parse_redirect_list() {
	ast_node *redirect, *redirect_list = malloc(sizeof(ast_node));
	ast_nodelist *tail_child;
	redirect_list->type = REDIRECTLIST;
	redirect = parse_redirect();
	if (redirect != NULL) {
		redirect_list->children = malloc(sizeof(ast_node));
		redirect_list->children->node = redirect;
		redirect_list->children->next = NULL;
		tail_child = redirect_list->children;
		redirect = parse_redirect();
	}

	while (redirect != NULL) {
		tail_child->next = malloc(sizeof(ast_nodelist));
		tail_child = tail_child->next;
		tail_child->node = redirect;
		tail_child->next = NULL;
		redirect = parse_redirect();
	}
	return redirect_list;
}

ast_node *parse_redirect() {
	int redirect_type;
	ast_node *arg, *redirect;
	if (tokens == NULL || !is_redirect_token()) {
		return NULL;
	}

	redirect_type = is_redirect_token();
	strip_head();
	arg = parse_arg();
	strip_head();
	
	redirect = malloc(sizeof(ast_node));
	redirect->children = malloc(sizeof(ast_nodelist));
	redirect->children->node = arg;
	redirect->children->next = NULL;

	switch (redirect_type) {
		case 4:
			redirect->type = STDIN_REDIRECT;
			break;
		case 1:
			redirect->type = STDOUT_REDIRECT;
			break;
		case 2:
			redirect->type = STDERR_REDIRECT;
			break;
	}

	return redirect;
}

ast_node *parse_background_key() {
	strip_head();
	ast_node *background_key = malloc(sizeof(ast_node));
	background_key->type = BACKGROUND_KEY;
	background_key->children = NULL;
	return background_key;
}


ast_node *parse_arg() {
	if (tokens == NULL || is_special_token()) {
		return NULL;
	}

	if (tokens->str[0] == '$') {
		return parse_variable_expression();
	}

	if (tokens->str[0] == '#' && tokens->str[1] == 'D' && tokens->str[2] == ':') {
		return parse_data_variable();
	}

	return parse_value();
}

ast_node *parse_value() {
	ast_node *value = malloc(sizeof(ast_node));
	value->children = NULL;
	value->type = VALUE;
	strncpy(value->token, tokens->str, MAX_TOKEN_LENGTH);
	return value;
}

ast_node *parse_variable_expression() {
	int i, varlen = strlen(tokens->str);
	ast_node *variable = malloc(sizeof(ast_node));
	variable->type = VARIABLE;
	variable->children = NULL;
	for (i = 0; i < varlen; i++) {
		variable->token[i] = tokens->str[i + 1];
	}
	return variable;
}

ast_node *parse_data_variable() {
	ast_node *data_variable;
	int i, varlen = strlen(tokens->str);
	data_variable = malloc(sizeof(ast_node));
	data_variable->type = DATA_VARIABLE;
	for (i = 0; i < varlen; i++) {
	 data_variable->token[i] = tokens->str[i + 3];
	}
	return data_variable;
}

ast_node *parse_negated_command() {
	ast_node *negated_command = malloc(sizeof(ast_node));
	negated_command->type = NEGATED_COMMAND;
	strip_head();
	negated_command->children = malloc(sizeof(ast_nodelist));
	negated_command->children->next = NULL;
	negated_command->children->node = parse_command();
	return negated_command;
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

ast_node *parse_network_command(int colonidx) {
	strlist *ssh_token, *hostname_token;
	/* Insert new tokens for the ssh cmd and hostname. */
	ssh_token = malloc(sizeof(strlist));
	hostname_token = malloc(sizeof(strlist));
	strncpy(ssh_token->str, "ssh", MAX_TOKEN_LENGTH);

	/* Nullify the colon to split the string. Take the first half as hostname. */
	tokens->str[colonidx] = '\0';
	strncpy(hostname_token->str, tokens->str, MAX_TOKEN_LENGTH);

	/* Copy the latter (command) portion of the original head of tokens to the
	 * front of the string.
	 */
	strncpy(tokens->str, &tokens->str[colonidx+1], MAX_TOKEN_LENGTH - (colonidx + 1));
	/* Set the ssh token to point to the hostname token and the hostname token
	 * to point to the orginal command. Then make the ssh token the head of the
	 * tokens linked list.
	 */
	ssh_token->next = hostname_token;
	hostname_token->next = tokens;
	tokens = ssh_token;
	return parse_command();
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

/* Returns the index of the colon character within the string or
 * -1 if none is present.
 */
int contains_colon(char *str) {
	int i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == ':') {
			return i;
		}
	}
	return -1;
}


int is_special_token() {
	/* Piggyback off other helpers. */
	if (is_redirect_token() || is_background_key()) {
		return 1;
	}

	if (strcmp(tokens->str, "&&") == 0) {
		return 1;
	} else if (strcmp(tokens->str, "||") == 0) {
		return 1;
	} else {
		return 0;
	}
}

/* Returns 4 if stdin redirect, 1 if stdout, 2 if stderr or 0 if not
 * a redirect.r
 */
int is_redirect_token() {
	if (strcmp(tokens->str, "<") == 0) {
		return 4;
	} else if (strcmp(tokens->str, ">") == 0) {
		return 1;
	} else if (strcmp(tokens->str, "2>") == 0) {
		return 2;
	} else {
		return 0;
	}
}

int is_background_key() {
	if (strcmp(tokens->str, "&") == 0) {
		return 1;
	} else {
		return 0;
	}
}

int is_negation(char *str) {
	if (strcmp(str, "!") == 0) {
		return 1;
	} else {
		return 0;
	}
}

void parser_error() {
	fprintf(stderr, "Parser error\n");
	return;
}

