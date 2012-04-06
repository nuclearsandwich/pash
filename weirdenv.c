#include <stdio.h>
#include <stdlib.h>

int main() {
	setenv("?1", "PENS", 1);
	printf("This is the value of $?1: %s\n", getenv("?1"));
	return 0;
}

