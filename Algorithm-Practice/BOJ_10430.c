#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int A, B, C;

	scanf("%d %d %d", &A, &B, &C);

	printf("%d\n", (A + B) % C);
	printf("%d\n", (A % C + B % C) % C);
	printf("%d\n", (A * B) % C);
	printf("%d\n", (A % C * B % C) % C);

	return 0;
}