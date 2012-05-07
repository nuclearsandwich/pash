#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/interpreter.h"

/* A Non-zero integer for overwriting environment variables with setenv */
#define OVERWRITE 1

void interpret(ast_node *root) {
	int exit_status;
	if (root->type == COMMAND) {
		exit_status = interpret_command(root);
	} else if (root->type == VARASSIGN) {
		exit_status = interpret_var_assign(root);
	}

	fifo_push(MAX_SAVED_EXITSTATUSES, exitstatuses, exitstatus_head, exit_status);
	set_exitstatuses();
	/* Free AST */
	/* Free tokens */
	return;
}

int interpret_command(ast_node* command) {
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
	return WEXITSTATUS(cmdstats);
}

int interpret_var_assign(ast_node *var_assign) {
	char *varname, *value;
	varname = var_assign->children->node->token;
	value = var_assign->children->next->node->token;
	return setenv(varname, value, OVERWRITE);
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

void set_exitstatuses() {
	int i, status;
	char var[2]; /* Only need 3 characters. Since statuses range from 0-255. */
	char val[3]; /* Only need 3 characters. Since statuses range from 0-255. */
	for (i = 0; i < MAX_SAVED_EXITSTATUSES; i++) {
		sprintf(var, "?%1d", i);
		status = fifo_peek(MAX_SAVED_EXITSTATUSES, exitstatuses,
				exitstatus_head, i);
		if (status != UNSET_STATUS) {
			sprintf(val, "%3d", status);
			setenv(var, val, OVERWRITE);
		} else {
			unsetenv(var);
		}
	}
	return;
}

