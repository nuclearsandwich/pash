#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *prompt_string(char *prompt_template, int line_count);

int line_count = 0;
char *prompt_template = "[%i]~>";


char * echo() {
	char *input = readline(prompt_string(
		prompt_template, line_count));
	++line_count;
	return input;
}

char *prompt_string(char *prompt_template, int line_count) {
	char *ps = "";
	sprintf(ps, prompt_template, line_count);
	return ps;
}


int main() {
	char* user_response = "Welcome to echo";
	if (user_response[0] == 'Q') {
		return 0;
	} else {
		user_response = echo();
		puts(user_response);
	}

	return 0;
}

