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
	command->children = NULL;
	return command;
}
	
