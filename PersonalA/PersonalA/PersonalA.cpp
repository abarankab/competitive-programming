// PersonalA.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

#define next228 next;
#define int long long

using namespace std;

struct event
{
	int type;
	int time;
	int id;

	event() {}

	event(int _type, int _time, int _id)
	{
		type = _type;
		time = _time;
		id = _id;
	}
};

bool operator<(event a, event b)
{
	if (a.time == b.time && a.type != b.type)
	{
		return a.type > b.type;
	}
	return a.time > b.time;
}

int ts, tf, t, n, cnt;
queue<event> q;
priority_queue<event> events;
set<int> used;

vector<int> first_time;

signed main()
{
	cin >> ts >> tf >> t >> n;

	for (int i = 0; i < n; ++i)
	{
		int time;
		cin >> time;

		events.push(event(0, time, cnt++));
		first_time.push_back(time);
		if (used.count(time - 1) == 0)
		{
			events.push(event(1, time - 1, cnt++));
			first_time.push_back(time - 1);
		}
	}
	events.push(event(-100, ts, -1));
	events.push(event(-50, tf, -1));

	int next = ts;
	int res_time = 1e12 + 228;
	int res = 1e12 + 228;
	bool mode = 0;
	while (true)
	{
		if (mode == 0)
		{
			event now = events.top();
			if (events.top().type == -100)
			{
				events.pop();

				if (!q.empty())
				{
					if (q.front().type == 1)
					{
						events.push(event(-2, next + t, q.front().id));
					}
					else
					{
						events.push(event(-3, next + t, q.front().id));
					}
				}
				mode = 1;
			}
			else
			{
				q.push(events.top());
				events.pop();
			}
		}
		else
		{
			if (events.top().type == -50)
			{
				break;
			}
			else if (events.top().type == -2)
			{
				event now = events.top();
				events.pop();
				if (res > now.time - first_time[now.id])
				{
					res = now.time - first_time[now.id];
					res_time = first_time[now.id];
				}

				if (!q.empty())
				{
					if (q.front().type == 1)
					{
						events.push(event(-2, next + t, q.front().id));
					}
					else
					{
						events.push(event(-3, next + t, q.front().id));
					}
				}
				else
				{
					if (0 < res)
					{
						res = 0;
						res_time = next;
						break;
					}
				}
			}
			else if (events.top().type == -3)
			{
				event now = events.top();
				events.pop();
				next = now.time;

				if (!q.empty())
				{
					if (q.front().type == 1)
					{
						events.push(event(-2, next + t, q.front().id));
					}
					else
					{
						events.push(event(-3, next + t, q.front().id));
					}
				}
				else
				{
					if (0 < res)
					{
						res = 0;
						res_time = next;
					}
				}
			}
			else
			{
				q.push(events.top());
				events.pop();
			}
		}
	}

	cout << res_time;

	return 0;
}