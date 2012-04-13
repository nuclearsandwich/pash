#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char* getinput(char* prompt_string) {
	return readline(prompt_string);
}
