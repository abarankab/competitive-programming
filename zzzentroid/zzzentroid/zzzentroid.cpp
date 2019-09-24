// zzzentroid.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

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

void build(int v, int pr = -1)
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

void dfs(int v, int pr = 0)
{
	tin[v] = cnt++;
	used[v] = 1;
	dp[v][0] = pr;

	for (int k = 1; k <= EXP; ++k)
	{
		dp[v][k] = dp[dp[v][k - 1]][k - 1];
	}

	h[v] = v == 0 ? 0 : h[pr] + 1;

	for (int u : g[v])
	{
		if (!used[u])
		{
			dfs(u, v);
		}
	}

	tout[v] = cnt++;
}

void preproc()
{
	dfs(0);
	memset(used, 0, sizeof(used));
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
	cin >> n >> m;
	for (int i = 0; i < n - 1; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	preproc();
	build(0);

	for (int i = 0; i < MAXN; ++i)
	{
		res[i] = INF;
	}

	color(0);

	for (int qn = 0; qn < m; ++qn)
	{
		int t, v;
		cin >> t >> v;
		if (t == 1)
		{
			color(v - 1);
		}
		else
		{
			cout << get(v - 1) << endl;
		}
	}
	return 0;
}

