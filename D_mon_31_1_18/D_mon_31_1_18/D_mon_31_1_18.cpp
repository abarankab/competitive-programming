// D_mon_31_1_18.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;

int n, m;
string s;
vector<int> g[MAXN];
vector<vector<int> > dp;
int used[300005];
int cnt;
int col[300005];
bool flag;
vector<int> order;
int res;

void dfs_init(int v)
{
	col[v] = 1;
	for (auto u : g[v])
	{
		if (col[u] == 1)
		{
			flag = 1;
		}
		else if (!col[u])
		{
			dfs_init(u);
		}
	}
	col[v] = 2;
	order.push_back(v);
}

void dfs(int v, int pr = -1)
{
	used[v] = 1;

	if (pr != -1)
	{
		for (int let = 0; let < 26; ++let)
		{
			dp[v][let] = max(dp[pr][let] + (s[v] == 'a' + let), dp[v][let]);
		}
	}

	for (auto u : g[v])
	{
		if (!used[u])
		{
			dfs(u, v);
		}
	}
}

int main()
{
	cin >> n >> m;
	dp.resize(n, vector<int> (26, 0));
	cin >> s;
	for (int i = 0; i < n; ++i)
	{
		++dp[i][s[i] - 'a'];
	}
	for (int i = 0; i < m; ++i)
	{
		int x, y;
		cin >> x >> y;
		g[--x].push_back(--y);
	}
	for (int i = 0; i < n; ++i)
	{
		dfs_init(0);
	}
	if (flag)
	{
		cout << -1 << endl;
		return 0;
	}
	reverse(order.begin(), order.end());
	for (auto v : order)
	{
		for (auto u : g[v])
		{
			for (int let = 0; let < 26; ++let)
			{
				dp[u][let] = max(dp[v][let] + (s[u] == 'a' + let), dp[u][let]);
			}
		}
		res = max(res, *max_element(dp[v].begin(), dp[v].end()));
	}
	cout << res << endl;
    return 0;
}

