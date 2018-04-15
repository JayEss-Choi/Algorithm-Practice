#include <iostream>
#include <cstring>


int main(int argc, char *argv[])
{
	int answer;
	int arr[100][100];
	int sum_i[100], sum_j[100], sum_x[2];
	int max_i, max_j, max_x;
	int dummy;

	for (int t = 0; t < 10; t++)
	{
		answer = max_i = max_j = max_x = 0;
		memset(arr, 0, 100 * 100 * sizeof(int));
		memset(sum_i, 0, 100 * sizeof(int));
		memset(sum_j, 0, 100 * sizeof(int));
		memset(sum_x, 0, 2 * sizeof(int));

		scanf("%d", &dummy);

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				scanf("%d", &arr[i][j]);
				sum_i[i] += arr[i][j];
				sum_j[j] += arr[i][j];
				if (i == j)
					sum_x[0] += arr[i][j];
				if (i + j == 99)
					sum_x[1] += arr[i][j];
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (max_i < sum_i[i])
				max_i = sum_i[i];
			if (max_j < sum_j[i])
				max_j = sum_j[i];
		}
		max_x = (sum_x[0] > sum_x[1]) ? sum_x[0] : sum_x[1];

		answer = (max_i > max_j) ? max_i : max_j;
		answer = (answer > max_x) ? answer : max_x;

		printf("#%d %d\n", t + 1, answer);
	}

	return 0;
}