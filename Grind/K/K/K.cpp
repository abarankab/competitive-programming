// Day1_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>

using namespace std;

const int MAXN = 100005;

struct edge
{
	int to, val;
	bool clean;

	edge() {}

	edge(int _to, int _val, int _clean)
	{
		to = _to;
		val = _val;
		clean = _clean;
	}
};

int n, tm;
vector<edge> g[MAXN], g2[MAXN];
long double sz[MAXN];
bool used[MAXN];
long double all_dist, all_q, all_dist2, all_q2;

void get2(int v, int pr = -1)
{
	used[v] = 1;
	sz[v] = 1;
	for (edge u : g2[v])
	{
		if (u.to != pr)
		{
			get2(u.to, v);
			sz[v] += sz[u.to];
		}
	}
}

void count2(int v, int rt, int pr = -1)
{
	for (edge u : g2[v])
	{
		if (u.to != pr)
		{
			count2(u.to, rt, v);
			all_dist2 += u.val * (sz[rt] - sz[u.to]) * sz[u.to];
		}
	}
}

void get(int v, int pr = -1)
{
	used[v] = 1;
	sz[v] = 1;
	for (edge u : g[v])
	{
		if (u.to != pr)
		{
			get(u.to, v);
			sz[v] += sz[u.to];
		}
	}
}

void cnt(int v, int rt, int pr = -1)
{
	for (edge u : g[v])
	{
		if (u.to != pr)
		{
			cnt(u.to, rt, v);
			all_dist += u.val * (sz[rt] - sz[u.to]) * sz[u.to];
		}
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n - 1; ++i)
	{
		int u, v, val, clean;
		cin >> u >> v >> val >> clean;
		--u; --v;
		if (!clean)
		{
			g2[u].push_back(edge(v, val, clean));
			g2[v].push_back(edge(u, val, clean));
		}
		g[u].push_back(edge(v, val, clean));
		g[v].push_back(edge(u, val, clean));
	}

	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			get2(i);
			count2(i, i);
			all_q2 += sz[i] * (sz[i] - 1) / 2;
		}
	}
	memset(used, 0, MAXN * sizeof(bool));
	memset(sz, 0, MAXN * sizeof(int));
	get(0);
	cnt(0, 0);
	all_q += sz[0] * (sz[0] - 1) / 2;

	cout.precision(20);
	if (!(all_q - all_q2))
	{
		cout << 0 << endl;
		return 0;
	}
	cout << fixed << (all_dist - all_dist2) / (all_q - all_q2) << endl;
	return 0;
}

/*
5
1 2 1 1
1 3 4 0
3 4 2 1
3 5 2 0

5
1 2 5 0
1 3 3 1
3 4 2 0
3 5 7 0
*/