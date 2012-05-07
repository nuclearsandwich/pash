#ifndef SH142TYPES
#include "sh142types.h"
#endif

#include "fifo.h"
/* The interpreter for the sh142 command shell. Works on a tree of ASTNodes */

void interpret(ast_node *root);
int interpret_command(ast_node *command);
int interpret_var_assign(ast_node *var_assign);
char *interpret_variable(ast_node *variable);
char *interpret_value(ast_node *value);

/* Variables for the Exit Status FIFO. */
#define UNSET_STATUS -99
int *exitstatus_head;
int exitstatuses[MAX_SAVED_EXITSTATUSES];
void set_exitstatuses(void);
