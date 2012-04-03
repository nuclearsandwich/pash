#include <stdio.h>
#include <stdlib.h>
#include "input_reader.h"
#include "environment_table.h"

#define PROMPT_STRING "sh142$ "
#define loop while(1)

void process_command(char *command_with_args);

int main() {
	loop {
		process_command("echo Hello World!");
		exit(12);
	}

	return 0;
}

void process_command(char *command_with_args) {
	printf("proccessing command %s\n", command_with_args);
	return;
}

