#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/interpreter.h"

/* A Non-zero integer for overwriting environment variables with setenv */
#define OVERWRITE 1

void interpret(ast_node *root) {
	if (root->type == COMMAND) {
		interpret_command(root);
		return;
	} else if (root->type == VARASSIGN) {
		interpret_var_assign(root);
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

void interpret_var_assign(ast_node *var_assign) {
	char *varname, *value;
	varname = var_assign->children->node->token;
	value = var_assign->children->next->node->token;
	setenv(varname, value, OVERWRITE);
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

