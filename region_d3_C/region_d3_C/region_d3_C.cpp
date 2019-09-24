// region_d3_C.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

struct bit
{
	int val;

	void on(int pos)
	{
		val |= (1 << pos);
	}

	void off(int pos)
	{
		val |= (1 << pos);
		val ^= (1 << pos);
	}

	bool get(int pos)
	{
		return (val << pos) & 1;
	}

	bit()
	{
		val = 0;
	}
};

vector<int> pay;
vector<int> cash;
vector<vector<bit> > can;
int n, m, sum;
bool flag;
bit now;

void gen(int cur = 0)
{
	if (cur == m)
	{
		for (int i = 0; i < n; ++i)
		{
			if (pay[i] == sum)
			{
				can[i].push_back(now);
			}
		}
	}
	else
	{
		now.on(cur);
		sum += cash[cur];
		gen(cur + 1);
		now.off(cur);
		sum -= cash[cur];
		gen(cur + 1);
	}
}

void gen2(int cur = 0, int now = 0)
{
	if (cur == n)
	{
		flag = 1;
		return;
	}
	for (int i = 0; i < can[cur].size(); ++i)
	{
		if ((int)(can[cur][i].val & now) == 0)
		{
			gen2(cur + 1, now | can[cur][i].val);
		}
	}
}

int main()
{
	mt19937 rnd;
	srand(rnd());

	cin >> n >> m;
	can.resize(n);
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		pay.push_back(tmp);
	}
	for (int i = 0; i < m; ++i)
	{
		int tmp;
		cin >> tmp;
		cash.push_back(tmp);
	}
	gen();
	gen2();
	if (flag)
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}
    return 0;
}

