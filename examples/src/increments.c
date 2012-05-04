#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 0;
	char* v = "What is this I don't even";
	while (i < 7) {
		printf("The %dth character is %c\n", i, v[i++]);
	}
	return 0;
}

