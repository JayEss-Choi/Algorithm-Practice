#include <stdio.h>

int main(void) {
	char str[101];
	while (fgets(str, 1001, stdin) != NULL)
		fputs(str, stdout);
	return 0;
}
