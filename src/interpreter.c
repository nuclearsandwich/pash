#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/interpreter.h"

void interpret(ast_node *root) {
	if (root->type == COMMAND) {
		interpret_command(root);
		return;
	}
	/* Free AST */
	/* Free tokens */
	return;
}

void interpret_command(ast_node* command) {
	int cmdstats, argc = 0;
	pid_t cmdpid;
	char *argv[MAX_TOKEN_LENGTH];
	ast_nodelist *arg = command->children;
	/* Build the values to pass to execvp */
	argv[argc] = interpret_value(command);
	++argc;
	while (arg != NULL) {
		if (arg->node->type == VARIABLE) {
			argv[argc] = interpret_variable(arg->node);
		} else {
			argv[argc] = interpret_value(arg->node);
		}
		++argc;
		arg = arg->next;
	}

	/* Null-terminate the list as per execvp's documentation. */
	argv[argc] = NULL;
	cmdpid = fork();
	if (!cmdpid)  {
		execvp(command->token, argv);
	} else {
		waitpid(cmdpid, &cmdstats, 0);
	}
	return;
}

char *interpret_variable(ast_node *variable) {
	char *value = (char*)malloc(sizeof(char) * MAX_STRING_LENGTH);
	char *envar = getenv(variable->token);
	if (envar != NULL) {
		strncpy(value, envar, MAX_STRING_LENGTH);
	} else {
		strncpy(value, "", MAX_STRING_LENGTH);
	}
	return value;
}

char *interpret_value(ast_node *value) {
	return value->token;
}

