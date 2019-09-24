// Day4_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
int n, m, res = 0;
vector<int> g[MAXN];
bool used[MAXN];

void dfs(int v, int cnt = 0)
{
	used[v] = 1;
	++cnt;
	res = max(res, cnt);

	for (int u : g[v])
	{
		if (!used[u] && g[u].size() < 3)
		{
			dfs(u, cnt);
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
		--u;
		--v;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	for (int i = 0; i < n; ++i)
	{
		if (g[i].size() == 1)
		{
			dfs(i);
		}
	}
	cout << res << endl;
    return 0;
}

