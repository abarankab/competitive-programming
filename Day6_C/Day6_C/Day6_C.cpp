// Day6_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 310;
int n, cnt;
vector<int> arr[MAXN];
vector<int> g[MAXN];
vector<int> f[2 * MAXN];
vector<int> l[MAXN];
int pr[2 * MAXN];
bool used[MAXN];
map<string, int> mp;
int res = 0;

bool ok(vector<int> from, vector<int> to)
{
	for (int check : from)
	{
		bool found = false;
		for (int now : to)
		{
			if (now == check)
			{
				found = true;
			}
		}
		if (!found)
		{
			return false;
		}
	}
	return true;
}

bool gfs(int v)
{
	if (used[v])
	{
		return false;
	}
	used[v] = true;
	for (int u : f[v])
	{
		if (pr[u] == -1 || gfs(pr[u]))
		{
			pr[u] = v;
			return true;
		}
	}
	return false;
}

void dfs(int v)
{
	used[v] = 1;
	for (int u : l[v])
	{
		if (!used[u])
		{
			dfs(u);
		}
	}
}

signed main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j)
		{
			string now;
			cin >> now;
			if (!mp.count(now))
			{
				mp[now] = cnt++;
			}
			arr[i].push_back(mp[now]);
		}
	}
	mp.clear();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i != j && ok(arr[i], arr[j]))
			{
				g[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int u : g[i])
		{
			f[i].push_back(n + u);
		}
	}
	cnt = 0;

	for (int i = 0; i < 2 * MAXN; ++i)
	{
		pr[i] = -1;
	}

	for (int v = 0; v < n; ++v)
	{
		memset(used, 0, MAXN);
		gfs(v);
	}
	memset(used, 0, MAXN);
	for (int i = 0; i < n; ++i)
	{
		if (pr[i + n] != -1)
		{
			l[i].push_back(pr[i + n]);
			l[pr[i + n]].push_back(i);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			dfs(i);
			++cnt;
		}
	}
	cout << cnt << endl;
    return 0; 
}
