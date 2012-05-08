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
	if (root->type == VARASSIGN) {
		exit_status = interpret_var_assign(root);
	} else {
		exit_status = interpret_command(root);
	}

	fifo_push(MAX_SAVED_EXITSTATUSES, exitstatuses, exitstatus_head, exit_status);
	set_exitstatuses();
	free_ast(root);
	return;
}

int interpret_command(ast_node* command) {
	int cmdstats, argc = 0, execerr;
	pid_t cmdpid;
	char *argv[MAX_TOKEN_LENGTH];
	FILE *stinf, *stoutf, *sterrf;
	ast_node *redirect_list;
	ast_nodelist *arg, *redirect, *remaining_children;
	remaining_children = command->children;
	stinf = stoutf = sterrf = NULL;


	/* Build the values to pass to execvp */
	argv[argc] = interpret_value(command);
	++argc;

	if (remaining_children != NULL && remaining_children->node->type == ARGLIST) {
		arg = remaining_children->node->children;

		while (arg != NULL) {
			argv[argc] = interpret_arg(arg->node);
			++argc;
			arg = arg->next;
		}
		remaining_children = remaining_children->next;
	}

	if (remaining_children != NULL && remaining_children->node->type == REDIRECTLIST) {
		redirect_list = remaining_children->node;
		remaining_children = remaining_children->next;
	} else {
		redirect_list = NULL;
	}

	/* Null-terminate the list as per execvp's documentation. */
	argv[argc] = NULL;
	cmdpid = fork();
	if (!cmdpid)  {
		if (redirect_list != NULL) {
			redirect = redirect_list->children;

			while (redirect != NULL) {
				switch(redirect->node->type) {
					case STDIN_REDIRECT:
						stinf = fopen(
								interpret_arg(redirect_list->children->node->children->node),"r");
						break;
					case STDOUT_REDIRECT:
						stoutf = fopen(
								interpret_arg(redirect_list->children->node->children->node), "w");
						break;
					case STDERR_REDIRECT:
						sterrf = fopen(
								interpret_arg(redirect_list->children->node->children->node), "w");
						break;
				}
				redirect = redirect->next;
			}
		}

		if (stinf != NULL) {
			dup2(fileno(stinf), fileno(stdin));
		}
		if (stoutf != NULL) {
			dup2(fileno(stoutf), fileno(stdout));
		}
		if (sterrf != NULL) {
			dup2(fileno(sterrf), fileno(stderr));
		}

		execerr = execvp(command->token, argv);
		if (execerr == -1) {
			fprintf(stderr, "sh142: %s: command not found.\n", argv[0]);
			exit(127);
		}
	} else {
		waitpid(cmdpid, &cmdstats, 0);
	}
	return WEXITSTATUS(cmdstats);
}

int interpret_negated_command(ast_node *command) {
	int command_status;
	command_status = interpret_command(command);
	if (command_status == 0) {
		return 1;
	} else {
		return 0;
	}
}

int interpret_var_assign(ast_node *var_assign) {
	char *varname, *value;
	varname = var_assign->children->node->token;
	value = var_assign->children->next->node->token;
	return setenv(varname, value, OVERWRITE);
}

char *interpret_arg(ast_node *arg) {
	if (arg->type == VARIABLE) {
		return interpret_variable(arg);
	} else if (arg->type == DATA_VARIABLE) {
		return interpret_data_variable(arg);
	} else {
		return interpret_value(arg);
	}
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

char *interpret_data_variable(ast_node *data_variable) {
	return resolve_data(data_variable->token);
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

void free_ast(ast_node *root) {
	if (root != NULL) {
		if (root->children == NULL) {
			free(root);
		} else {
			free_ast_list(root->children);
		}
	}
}

void free_ast_list(ast_nodelist *list) {
	ast_nodelist *next;
	while (list != NULL) {
		next = list->next;
		free_ast(list->node);
		free(list);
		list = next;
	}
}

