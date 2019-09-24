// zzzentroid.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int MAXN = (int)1e5 + 5;
const int EXP = 20;
const int INF = (int) 1e9;

int n, m;
vector<int> g[MAXN];
int dp[MAXN][EXP + 1];
int h[MAXN];
int sz[MAXN];
bool used[MAXN];
vector<int> order;
int pc[MAXN];
int res[MAXN];
int tin[MAXN];
int tout[MAXN];
int cnt = 0;
map<int, int> col;

void count_sizes(int v, int pr_v)
{
	order.push_back(v);
	used[v] = 1;
	sz[v] = 1;

	for (int u : g[v])
	{
		if (u != pr_v)
		{
			count_sizes(u, v);
			sz[v] += sz[u];
		}
	}
}

int get_centroid(int v)
{
	order.clear();
	count_sizes(v, v);
	int full_size = sz[v] / 2;
	bool flag = true;

	for (int i = 0; i < order.size(); ++i)
	{
		for (int u : g[order[i]])
		{
			if (sz[u] > full_size)
			{
				flag = false;
			}
		}
		if (flag)
		{
			return v;
		}
		flag = true;
	}
}

void build(int v = 0, int pr = -1)
{
	v = get_centroid(v);
	pc[v] = pr;

	if (g[v].size() == 0)
	{
		return;
	}
	for (int u : g[v])
	{
		g[u].erase(find(g[u].begin(), g[u].end(), v));
	}
	for (int u : g[v])
	{
		build(u, v);
	}
}

bool ancestor(int u, int v)
{
	return tin[u] <= tin[v] && tout[u] >= tin[v];
}

int lca(int u, int v)
{
	if (ancestor(u, v)) return u;
	if (ancestor(v, u)) return v;
	int k = EXP;
	while (k >= 0)
	{
		if (!ancestor(dp[v][k], u))
		{
			v = dp[v][k];
		}
		--k;
	}
	return dp[v][0];
}

int dist(int u, int v)
{
	int lc = lca(u, v);
	return (h[u] - h[lc]) + (h[v] - h[lc]);
}

int get(int v)
{
	int u = v;
	int ans = INF;
	while (v != -1)
	{
		ans = min(ans, res[v] + dist(u, v));
		v = pc[v];
	}
	return ans;
}

void color(int v)
{
	int u = v;
	while (v != -1)
	{
		res[v] = min(res[v], dist(u, v));
		v = pc[v];
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n - 1; ++i)
	{
		int pt;
		cin >> pt;
		g[pt].push_back(i);
		g[i].push_back(pt);
	}
	build();

	for (int i = 0; i < MAXN; ++i)
	{
		res[i] = INF;
	}
	return 0;
}

