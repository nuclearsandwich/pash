#include <string.h>
char *chomp(char* str) {
	int i, len = strlen(str);
	char *chompedstr;
	if (str[len - 2] == '\n') {
		for (i = 0; i < len - 1; i++) {
			chompedstr[i] = str[i];
		}
	} else {
		return str;
	}
}
