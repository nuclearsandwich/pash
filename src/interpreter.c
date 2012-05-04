#include <stdlib.h>
#include <unistd.h>
#include "../include/interpreter.h"

void interpret(ast_node *root) {
	if (root->type == COMMAND) {
		interpret_command(root);
		return;
	}
	return;
}

void interpret_command(ast_node* command) {
	if (command->children == NULL) {
		execlp(command->token, command->token, NULL);
	}
}
