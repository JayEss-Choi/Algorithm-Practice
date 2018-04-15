#include <iostream>
#include <cstring>

int count[101];

int main(int argc, char *argv[])
{
	for (int t = 0; t < 10; t++)
	{
		int dummy;
		scanf("%d", &dummy);

		memset(count, 0, 101 * sizeof(int));

		for (int i = 0; i < 1000; i++)
		{
			int score;
			scanf("%d", &score);
			count[score]++;
		}

		int answer = 0;
		for (int i = 0; i < 101; i++)
			if (count[answer] <= count[i])
				answer = i;

		printf("#%d %d\n", t + 1, answer);
	}

	return 0;
}