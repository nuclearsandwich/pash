#ifndef SH142TYPES
#include "./sh142types.h"
#endif

/* The parser takes an input array of tokens and builds an
 * Abstract Syntax Tree for the following Grammar
 * CommandSequence ::= Command [Arglist]
 * CommandSequence ::= Command [Arglist] || CommandSequence
 * CommandSequence ::= Command [Arglist] && CommandSequence
 * Command ::= Command | NegatedCommand
 * Arglist ::= Argument [ Arglist ]
 */

/* Actual parsing functions */
ast_node *parse(strlist *tokens);
ast_node *parse_command_sequence(strlist *tokens);
ast_nodelist *parse_arglist(strlist *tokens);

/* strlist *destroy_head(strlist *list); */


