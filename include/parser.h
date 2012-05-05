#ifndef SH142TYPES
#include "./sh142types.h"
#endif

/* The parser takes an input array of tokens and builds an
 * Abstract Syntax Tree for the following Grammar
 * CommandSequence ::= Command [Arglist]
 * CommandSequence ::= Command [Arglist] || CommandSequence
 * CommandSequence ::= Command [Arglist] && CommandSequence
 * Command ::= Command | NegatedCommand | BackgroundCommand | BooleanCommand | PipedCommand
 * NegatedCommand ::= ! Command
 * BackgroundCommand ::= Command &
 * BooleanCommand ::= AndedCommand | OrredCommand
 * AndedCommand ::= Command && Command
 * OrredCommand ::= Command || Commmand
 * Arglist ::= Arg [ Arglist ]
 * Arg ::= Variable | Value
 * Variable ::= $Value
 */

strlist *tokens;

/* Actual parsing functions */
ast_node *parse(void);
ast_node *parse_command_sequence(void);
ast_nodelist *parse_arglist(void);
ast_node *parse_arg(void);
ast_node *parse_variable(void);
ast_node *parse_value(void);

void strip_head(void);


