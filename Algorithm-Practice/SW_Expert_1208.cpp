#include <iostream>
#include <cstring>

bool box[100][100];
struct Pos
{
	int i;
	int j;
} pos_high, pos_low;

void calc_high_pos()
{
	for (int j = 99; j >= 0; j--)
	{
		for (int i = 0; i < 100; i++)
		{
			if (box[i][j])
			{
				pos_high.i = i;
				pos_high.j = j;
				return;
			}
		}
	}
}

void calc_low_pos()
{
	for (int j = 0; j < 100; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			if (!box[i][j])
			{
				pos_low.i = i;
				pos_low.j = j - 1;
				return;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int N;  // ´ýÇÁ È½¼ö
	int h;  // »óÀÚÀÇ ³ôÀÌ
	int answer;

	for (int t = 0; t < 10; t++)
	{
		answer = 0;
		memset(box, 0, 100 * 100 * sizeof(bool));

		scanf("%d", &N);

		for (int i = 0; i < 100; i++)
		{
			scanf("%d", &h);
			for (int j = 0; j < h; j++)
			{
				box[i][j] = true;
			}
		}

		for (int n = 0; n < N; n++)
		{
			calc_high_pos();
			calc_low_pos();
			box[pos_high.i][pos_high.j] = false;
			box[pos_low.i][pos_low.j + 1] = true;
		}
		calc_high_pos();
		calc_low_pos();
		answer = pos_high.j - pos_low.j;

		printf("#%d %d\n", t + 1, answer);
	}

	return 0;
}