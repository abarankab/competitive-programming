// region_d1_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

const int MAXN = 200005;

vector<int> g[MAXN];
int dist[MAXN];
int overall[MAXN];
bool used[MAXN];

void setd(int v)
{
	queue<int> q;
	dist[v] = 0;
	q.push(v);
	used[v] = 1;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (int u : g[cur])
		{
			if (!used[u])
			{
				dist[u] = dist[cur] + 1;
				used[u] = 1;
				q.push(u);
			}
		}
	}
}

void dfs(int v, int p = -1, int cur = 0)
{
	overall[cur] += 1;
	for (int u : g[v])
	{
		if (u != p && cur + 1 == dist[u])
		{
			dfs(u, v, cur + 1);
		}
	}
}

int main()
{
	for (int i = 0; i < MAXN; ++i)
	{
		dist[i] = 2 * MAXN;
	}

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int a, b;
		cin >> a >> b;
		--a; --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	for (int i = 0; i < n; ++i)
	{
		setd(i);
		dfs(i);

		memset(used, 0, MAXN);
		for (int i = 0; i < MAXN; ++i)
		{
			dist[i] = 2 * MAXN;
		}
	}

	for (int i = MAXN - 1; i >= 0; --i)
	{
		if (overall[i] != 0)
		{
			cout << overall[i] / 2 << endl;
			break;
		}
	}

    return 0;
}

