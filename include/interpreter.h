#ifndef SH142TYPES
#include "sh142types.h"
#endif
/* The interpreter for the sh142 command shell. Works on a tree of ASTNodes */

void interpret(ast_node *root);

void interpret_command(ast_node *command);
