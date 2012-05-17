#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/wait.h>

#include "../include/chomp.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

/* The prompt string printed by Readline */
#define PROMPT_STRING "pash$ "

void load_config_files(void);
void prepare_fifo(void);
void input_loop(void);

int main() {
	prepare_fifo();
	load_config_files();
	input_loop();
	return 0;
}

void input_loop() {
	char *input;
	/* Begin main loop. */
	while(1) {
		input = readline(PROMPT_STRING);
		/* Break out when the user exits. */
		if (input == NULL || strcmp(input, "exit") == 0) {
			exit(0);
		}
		tokens = tokenize(input);
		interpret(parse());
	}
}

void load_config_files() {
	pid_t ls_pid;
	int ls_status;
	int fd[2];
	char lsbuffer[MAX_STRING_LENGTH], sourcebuffer[MAX_STRING_LENGTH];
	FILE *ls_output, *source_file;
	const char *fileext = ".pash\n";

	pipe(fd);
	ls_pid = fork();

	if (!ls_pid) {
		close(fileno(stdin));
		close(fileno(stdout));
		close(fileno(stderr));

		/* Attach stdout of ls command to pipe writing to parent. */
		dup2(fd[1], fileno(stdout));

		/* Doesn't work since * only expands from witin shell. :( */
		execlp("ls", "ls", NULL);
	} else {
		/* Close the write file descriptor in the parent. */
		close(fd[1]);
		waitpid(ls_pid, &ls_status, 0);
		ls_output = fdopen(fd[0], "r");

		while(fgets(lsbuffer, MAX_STRING_LENGTH, ls_output) != NULL) {
			if (strstr(lsbuffer, fileext) != NULL) {
				source_file = fopen(chomp(lsbuffer), "r");
				while(fgets(sourcebuffer, MAX_STRING_LENGTH, source_file) != NULL) {
					tokens = tokenize(chomp(sourcebuffer));
					interpret(parse());
				}
			}
		}
	}
	return;
}


void prepare_fifo() {
	int i;
	/* Set up exit status FIFO. */
	exitstatus_head = malloc(sizeof(int));
	*exitstatus_head = 0;
	for (i = 0; i < MAX_SAVED_EXITSTATUSES; i++) {
		exitstatuses[i] = UNSET_STATUS;
	}
}

