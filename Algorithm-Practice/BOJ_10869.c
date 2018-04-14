#include <stdio.h>

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);

	int add = a + b, sub = a - b, mul = a * b, div = a / b, mod = a % b;
	printf("%d\n%d\n%d\n%d\n%d\n", add, sub, mul, div, mod);

	return 0;
}
