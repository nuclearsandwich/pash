#include <string.h>
char *chomp(char* str) {
	int len = strlen(str);
	if (str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}
	return str;
}

