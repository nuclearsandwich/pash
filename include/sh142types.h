/* Protect from multiple inclusion */
#define SH142TYPES
/* The maximum size of a single token. */
#define MAX_TOKEN_LENGTH 64
#define MAX_STRING_LENGTH 256
#define MAX_SAVED_EXITSTATUSES 10

/* Different types of tokens!!!! */
typedef enum {
	VARASSIGN, VALUE, VARIABLE, COMMAND, NEGATED_COMMAND, ORRED_COMMAND,
	ANDED_COMMAND
} node_type;

/* Since we have mutually recursive structures, we need to use forward
 * declaration and thus, cannot omit the struct name.
 */
typedef struct sllist strlist;
typedef struct nodelist ast_nodelist;
typedef struct node ast_node;


struct node {
	node_type type;
	char token[MAX_TOKEN_LENGTH];
	ast_nodelist *children;
};

struct nodelist {
	ast_node *node;
	ast_nodelist *next;
};

struct sllist {
	char str[MAX_TOKEN_LENGTH];
	strlist *next;
};

