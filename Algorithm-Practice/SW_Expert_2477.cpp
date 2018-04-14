#include <iostream>
using namespace std;

int curr_time = -1;

class Visitor
{
public:
	int id;  // 고객 번호
	int ariv_tm;  // 도착 시간
	int reception_desk_id;  // 접수 창구 번호
	int repair_desk_id;  // 수리 창구 번호
};

class Desk
{
public:
	int id;  // 데스크 번호
	int curr_visitor_id;  // 현재 응대하는 고객 번호
	int proc_time;  // 건 당 처리 시간
	int job_time;  // 남은 처리 시간

public:
	Desk() : curr_visitor_id(0), job_time(0)
	{
	}

	void step()
	{
		if (job_time > 0)
			job_time--;
	}

	bool is_empty()
	{
		return (job_time == 0);
	}
};

// 고객 번호를 저장하는 큐
class Queue
{
public:
	int queue[1000];
	int f, r;

public:
	Queue() : f(0), r(0)
	{
	}

	void enqueue(int visitor_id)
	{
		queue[r++] = visitor_id;
	}

	int dequeue()
	{
		return queue[f++];
	}

	int size()
	{
		return r - f;
	}

	bool is_empty()
	{
		return (f == r);
	}
};

class Shop
{
public:
	int N, M, K;
	Visitor visitor[1000];
	Desk reception_desk[10], repair_desk[10];
	Queue reception_waiting_q, repair_waiting_q, finish_q;

public:
	Shop() {}

	void step()
	{
		curr_time++;

		for (int k = 0; k < K; k++)
			if (visitor[k].ariv_tm == curr_time)
				reception_waiting_q.enqueue(visitor[k].id);

		for (int m = 0; m < M; m++)
		{
			repair_desk[m].step();

			if (repair_desk[m].is_empty())
			{
				if (repair_desk[m].curr_visitor_id != 0)
				{
					finish_q.enqueue(repair_desk[m].curr_visitor_id);
					repair_desk[m].curr_visitor_id = 0;
				}
			}
		}

		for (int n = 0; n < N; n++)
		{
			reception_desk[n].step();

			if (reception_desk[n].is_empty())
			{
				if (reception_desk[n].curr_visitor_id != 0)
				{
					repair_waiting_q.enqueue(reception_desk[n].curr_visitor_id);
					reception_desk[n].curr_visitor_id = 0;
				}
			}
		}

		for (int m = 0; m < M; m++)
		{
			if (repair_desk[m].is_empty())
			{
				if (!repair_waiting_q.is_empty())
				{
					repair_desk[m].curr_visitor_id = repair_waiting_q.dequeue();
					repair_desk[m].job_time = repair_desk[m].proc_time;

					visitor[repair_desk[m].curr_visitor_id - 1].repair_desk_id = repair_desk[m].id;
				}
			}
		}

		for (int n = 0; n < N; n++)
		{
			if (reception_desk[n].is_empty())
			{
				if (!reception_waiting_q.is_empty())
				{
					reception_desk[n].curr_visitor_id = reception_waiting_q.dequeue();
					reception_desk[n].job_time = reception_desk[n].proc_time;

					visitor[reception_desk[n].curr_visitor_id - 1].reception_desk_id = reception_desk[n].id;
				}
			}
		}
	}
};


int main()
{
	int T;
	int N, M, K, A, B;
	int answer;

	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		Shop car_repair_shop;
		curr_time = -1;

		scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
		car_repair_shop.N = N;
		car_repair_shop.M = M;
		car_repair_shop.K = K;

		for (int n = 0; n < N; n++)
		{
			scanf("%d", &car_repair_shop.reception_desk[n].proc_time);
			car_repair_shop.reception_desk[n].id = n + 1;
		}

		for (int m = 0; m < M; m++)
		{
			scanf("%d", &car_repair_shop.repair_desk[m].proc_time);
			car_repair_shop.repair_desk[m].id = m + 1;
		}

		for (int k = 0; k < K; k++)
		{
			scanf("%d", &car_repair_shop.visitor[k].ariv_tm);
			car_repair_shop.visitor[k].id = k + 1;
		}
		
		while (car_repair_shop.finish_q.size() != K)
		{
			car_repair_shop.step();
		}

		answer = 0;
		for (int k = 0; k < K; k++)
		{
			if (car_repair_shop.visitor[k].reception_desk_id == A && car_repair_shop.visitor[k].repair_desk_id == B)
			{
				answer += car_repair_shop.visitor[k].id;
			}
		}
		if (answer == 0)
			answer = -1;
		printf("#%d %d\n", t, answer);
	}

	return 0;
}