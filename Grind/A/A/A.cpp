// A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 20005;
int n, m, timer;
vector<int> g[MAXN];
bool used[MAXN];
int tin[MAXN], f[MAXN];

void dfs(int v)
{
	tin[v] = timer++;
	f[v] = tin[v];
	for (int u : g[v])
	{
		if (!used[u])
		{
			dfs(u);
			f[v] = min(f[v], f[u]);
		}
		else
		{
			f[v] = min(f[v], tin[u]);
		}
	}
	
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int u = 0; u < n; ++u)
	{
		if (!used[u])
		{
			dfs(u);
		}
	}
    return 0;
}

