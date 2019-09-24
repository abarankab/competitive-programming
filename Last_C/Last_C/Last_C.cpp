// Last_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 405;

int n, m, k, t, q;
int p[MAXN];
bool used[MAXN];
bool lonely[MAXN];
vector<int> g[MAXN];
vector<pair<int, int> > res;

bool gfs(int v)
{
	if (used[v])
	{
		return false;
	}
	used[v] = true;
	for (int u : g[v])
	{
		if (p[u] == -1 || gfs(p[u]))
		{
			p[u] = v;
			return true;
		}
	}
	return false;
}

int main()
{
	cin >> m >> k >> n >> t;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			g[i].push_back(j);
		}
	}
	for (int i = 0; i < t; ++i)
	{
		int a, b;
		cin >> a >> b;
		--a; --b;
		b -= m;
		g[a].erase(remove(g[a].begin(), g[a].end(), b), g[a].end());
	}
	cin >> q;
	for (int i = 0; i < q; ++i)
	{
		int a;
		cin >> a;
		--a;
		lonely[a] = 1;
	}
	for (int i = m; i < m + k - n; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			if (!lonely[j + m])
			{
				g[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < m; ++i)
	{
		if (!lonely[i])
		{
			for (int j = k; j < m + k - n; ++j)
			{
				g[i].push_back(j);
			}
		}
	}
	memset(p, -1, MAXN * sizeof(int));
	for (int i = 0; i < m + k - n; ++i)
	{
		memset(used, 0, MAXN * sizeof(bool));
		gfs(i);
	}
	for (int i = 0; i < k + m - n; ++i)
	{
		if (p[i] == -1)
		{
			cout << "NO" << endl;
			return 0;
		}
		else if (i < k && p[i] < m)
		{
			res.push_back({p[i] + 1, i + m + 1});
		}
	}
	cout << "YES\n";
	for (int i = 0; i < res.size(); ++i)
	{
		cout << res[i].first << " " << res[i].second << "\n";
	}
	return 0;
}

