#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main (int argc, char *argv[]) {
	char *input;

	input = readline("PS: ");
	printf("Your input was ''%s''\n", input);

	return 0;
}
