#ifndef SH142TYPES
#include "./sh142types.h"
#endif

/* The parser takes an input array of tokens and builds an
 * Abstract Syntax Tree for the following Grammar
 *
 * Start              ::= Command | VarAssign | NetworkCommand
 * Command            ::= ['!'] Value [ ArgList ] [ RedirectList ] [ Chain ] [BackgroundKey]
 * ArgList            ::= Arg [ Arglist ]
 * Arg                ::= VariableExpression | Value
 * VariableExpression ::= [Arg]'$'Value[Arg]
 * VarAssign          ::= Value'='Arg
 * // Not Yet Implemented //
 * RedirectList       ::= Redirect [RedirectList]
 * Redirect           ::= StdinRedirect | StdoutRedirect | StderrRedirect
 * StdinRedirect      ::= '<' Arg
 * StdoutRedirect     ::= '>' Arg
 * StderrRedirect     ::= '2>' Arg
 * Chain              ::= AndedCommand | OrredCommand
 * AndedCommand       ::= '&&' Command
 * OrredCommand       ::= '||' Command
 * BackgroundKey      ::= '&'
 * NetworkCommand     ::= NodeName':'Command
 */

strlist *tokens;

/* Actual parsing functions */
ast_node *parse(void);
ast_node *parse_command(void);
ast_node *parse_arg_list(void);
ast_node *parse_arg(void);
ast_node *parse_var_assign(int eqlidx);
ast_node *parse_variable_expression(void);
ast_node *parse_value(void);
ast_node *parse_redirect_list(void);
ast_node *parse_redirect(void);

/* Helper functions */
void strip_head(void);
int contains_eql(char *str);
int is_special_token(void);
int is_redirect_token(void);


