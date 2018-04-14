#include <iostream>
#include <cstring>
using namespace std;


enum STATE {NOTHING, WALKING, ARRIVAL, DOWN, END};

int map[10][10];

struct Stairs
{
	int pos_i, pos_j;
	int length;
	int usage_count;
} stair[2];
int tmp_stair_idx;

struct Man
{
	int pos_i, pos_j;
	int ariv_tm;
	int start_tm;
	int end_tm;
	int state;
} man[2][10];
int tmp_man_idx;


int table[2][10][500];
int end_tm[10];


int main(int argc, char *argv[])
{
	int T, N;

	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		int answer = 0;
		tmp_stair_idx = 0;
		tmp_man_idx = 0;
		memset(map, 0, 10 * 10 * sizeof(int));
		memset(stair, 0, 2 * sizeof(Stairs));
		memset(man, 0, 10 * sizeof(Man));
		memset(table, 0, 2 * 10 * 500 * sizeof(int));
		memset(end_tm, 0, 10 * sizeof(int));

		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);

				if (map[i][j] > 1)
				{
					stair[tmp_stair_idx].pos_i = i;
					stair[tmp_stair_idx].pos_j = j;
					stair[tmp_stair_idx].length = map[i][j];
					tmp_stair_idx++;
				}
				else if (map[i][j] == 1)
				{
					man[0][tmp_man_idx].pos_i = i;
					man[0][tmp_man_idx].pos_j = j;
					man[0][tmp_man_idx].ariv_tm = 0;
					man[0][tmp_man_idx].start_tm = 0;
					man[0][tmp_man_idx].end_tm = 0;
					man[0][tmp_man_idx].state = WALKING;

					man[1][tmp_man_idx].pos_i = i;
					man[1][tmp_man_idx].pos_j = j;
					man[1][tmp_man_idx].ariv_tm = 0;
					man[1][tmp_man_idx].start_tm = 0;
					man[1][tmp_man_idx].end_tm = 0;
					man[1][tmp_man_idx].state = WALKING;

					tmp_man_idx++;
				}
			}
		}

		// Ç®ÀÌ
		for (int i = 0; i < tmp_man_idx; i++)
		{
			man[0][i].ariv_tm = abs(man[0][i].pos_i - stair[0].pos_i) + abs(man[0][i].pos_j - stair[0].pos_j);
			man[1][i].ariv_tm = abs(man[1][i].pos_i - stair[1].pos_i) + abs(man[1][i].pos_j - stair[1].pos_j);
		}

		for (int i = 0; i < 2; i++)
		{
			for (int time = 0; time < 500; time++)
			{
				for (int j = 0; j < tmp_man_idx; j++)
				{
					if (table[i][j][time] == END)
					{
						stair[i].usage_count--;
					}
					else if (time < man[i][j].ariv_tm)
					{
						table[i][j][time] = WALKING;
					}
					else if (time == man[i][j].ariv_tm)
					{
						table[i][j][time] = ARRIVAL;
					}
					else if (table[i][j][time - 1] == ARRIVAL)
					{
						if (stair[i].usage_count < 3)
						{
							stair[i].usage_count++;
							for (int k = 0; k < stair[i].length - 1; k++)
							{
								table[i][j][time +	k] = DOWN;
							}
							table[i][j][time + stair[i].length - 1] = END;
						}
						else if (stair[i].usage_count == 3)
						{
							table[i][j][time] = ARRIVAL;
						}
					}
				}
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < tmp_man_idx; j++)
			{
				for (int time = 0; time < 500; time++)
				{
					if (table[i][j][time] == END)
					{
						man[i][j].end_tm = time + 1;
					}
				}
			}
		}

		for (int i = 0; i < tmp_man_idx; i++)
		{
			end_tm[i] = (man[0][i].end_tm < man[1][i].end_tm) ? man[0][i].end_tm : man[1][i].end_tm;
		}

		for (int i = 0; i < tmp_man_idx; i++)
			if (answer < end_tm[i])
				answer = end_tm[i];

		printf("#%d %d\n", t + 1, answer);
	}

	return 0;
}