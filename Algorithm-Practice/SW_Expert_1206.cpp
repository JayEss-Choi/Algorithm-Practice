#include <iostream>
#include <cstring>

#define MAX_BUILDINGS 1000

int building[MAX_BUILDINGS];
int view[MAX_BUILDINGS];

int main(int argc, char *argv[])
{
	int n_buildings;
	int answer;

	for (int t = 0; t < 10; t++)
	{
		answer = 0;
		memset(building, 0, MAX_BUILDINGS * sizeof(int));
		for (int i = 0; i < MAX_BUILDINGS; i++)
		{
			view[i] = 0x7fffffff;
		}

		scanf("%d", &n_buildings);
		for (int n = 0; n < n_buildings; n++)
			scanf("%d", &building[n]);

		view[0] = view[1] = view[n_buildings - 1] = view[n_buildings - 2] = 0;
		for (int i = 2; i < n_buildings - 2; i++)
		{
			if (building[i] - building[i - 2] > 0 && view[i] > building[i] - building[i - 2])
				view[i] = building[i] - building[i - 2];
			else if (building[i] - building[i - 2] <= 0)
				view[i] = 0;

			if (building[i] - building[i - 1] > 0 && view[i] > building[i] - building[i - 1])
				view[i] = building[i] - building[i - 1];
			else if (building[i] - building[i - 1] <= 0)
				view[i] = 0;

			if (building[i] - building[i + 1] > 0 && view[i] > building[i] - building[i + 1])
				view[i] = building[i] - building[i + 1];
			else if (building[i] - building[i + 1] <= 0)
				view[i] = 0;

			if (building[i] - building[i + 2] > 0 && view[i] > building[i] - building[i + 2])
				view[i] = building[i] - building[i + 2];
			else if (building[i] - building[i + 2] <= 0)
				view[i] = 0;
		}
		for (int i = 0; i < n_buildings; i++)
			answer += view[i];

		printf("#%d %d\n", t + 1, answer);
	}

	return 0;
}
