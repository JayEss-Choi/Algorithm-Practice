#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX_N 8
#define MAX_K 5

struct Tile
{
	int height;
	int visit;
} map[MAX_N][MAX_N];

int T, N, K, answer;
int max_height, K_possible, tmp_answer;
int di[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };  // Left, Right, Up, Down

void dfs(int x, int y, int h, int *len)
{
	if (*len > answer)
		answer = *len;

	for (int i = 0; i < 4; i++)
	{
		if (x + di[i][0] < 0 || x + di[i][0] >= N || y + di[i][1] < 0 || y + di[i][1] >= N)
		{
			continue;
		}
		else if (map[x + di[i][0]][y + di[i][1]].visit == TRUE)
		{
			continue;
		}
		else
		{
			if (h > map[x + di[i][0]][y + di[i][1]].height)
			{
				map[x + di[i][0]][y + di[i][1]].visit = TRUE;
				*len += 1;
				dfs(x + di[i][0], y + di[i][1], map[x + di[i][0]][y + di[i][1]].height, len);
				*len -= 1;
				map[x + di[i][0]][y + di[i][1]].visit = FALSE;
			}
			else if (K_possible == TRUE && map[x + di[i][0]][y + di[i][1]].height - h < K)
			{
				K_possible = FALSE;
				map[x + di[i][0]][y + di[i][1]].visit = TRUE;
				*len += 1;
				dfs(x + di[i][0], y + di[i][1], h - 1, len);
				*len -= 1;
				map[x + di[i][0]][y + di[i][1]].visit = FALSE;
				K_possible = TRUE;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		memset(map, 0, MAX_N * MAX_N * sizeof(Tile));
		N = K = 0;
		K_possible = TRUE;
		max_height = 0;
		answer = tmp_answer = 1;

		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j].height);
				max_height = max_height < map[i][j].height ? map[i][j].height : max_height;
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j].height == max_height)
				{
					map[i][j].visit = TRUE;
					dfs(i, j, max_height, &tmp_answer);
					map[i][j].visit = FALSE;
					if (tmp_answer > answer)
						answer = tmp_answer;
				}
			}
		}

		printf("#%d %d\n", t, answer);
	}

	return 0;
}