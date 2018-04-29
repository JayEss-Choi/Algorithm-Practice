#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[101];
	while (fgets(str, 101, stdin) != NULL)
		fputs(str, stdout);

	return 0;
}
