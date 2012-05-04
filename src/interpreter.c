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
	int argc = 0;
	char *argv[MAX_TOKEN_LENGTH];
	ast_nodelist *arg = command->children;
	/* Build the values to pass to execvp */
	argv[argc] = command->token;
	++argc;
	while (arg != NULL) {
		argv[argc] = arg->node.token;
		++argc;
		arg = arg->next;
	}
	/* Null-terminate the list as per execvp's documentation. */
	argv[argc] = NULL;
	execvp(command->token, argv);
}
