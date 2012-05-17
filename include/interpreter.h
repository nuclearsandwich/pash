#ifndef PASHTYPES
#include "pashtypes.h"
#endif
#include "path_lookup.h"
#include "fifo.h"

/* The interpreter for the sh142 command shell. Works on a tree of ASTNodes */

void interpret(ast_node *root);
int interpret_command_seq(ast_node *command_seq);
int interpret_command(ast_node *command);
int interpret_negated_command(ast_node *command);
int interpret_var_assign(ast_node *var_assign);
char *interpret_arg(ast_node *arg);
char *interpret_variable(ast_node *variable);
char *interpret_data_variable(ast_node* data_variable);
char *interpret_value(ast_node *value);

/* Variables for the Exit Status FIFO. */
#define UNSET_STATUS -99
int *exitstatus_head;
int exitstatuses[MAX_SAVED_EXITSTATUSES];
void set_exitstatuses(void);

/* Cleanup */
void free_ast(ast_node *root);
void free_ast_list(ast_nodelist *list);
