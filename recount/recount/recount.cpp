// recount.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1e5;

vector<int> dict[MAXN];

vector<int> g[MAXN];
vector<int> gr[MAXN];
int col[MAXN];
bool used[MAXN];
bool used_r[MAXN];
bool flag = true;

void dfs(int v, int pr = -1)
{
	used[v] = true;

	if (pr != -1 && col[pr] == -1)
	{
		if(col[v] == 1)
		{
			flag = false;
		}
		col[v] = -1;
	}

	for (int u : g[v])
	{
		if (!used[u])
		{
			dfs(u, v);
		}
	}
}

void dfs_r(int v, int pr = -1)
{
	used_r[v] = true;

	if (pr != -1 && col[pr] == 1)
	{
		if (col[v] == -1)
		{
			flag = false;
		}
		col[v] = 1;
	}

	for (int u : g[v])
	{
		if (!used_r[u])
		{
			dfs_r(u, v);
		}
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		int len;
		cin >> len;
		for (int j = 0; j < len; ++j)
		{
			int let;
			cin >> let;
			dict[i].push_back(let);
		}
	}

	for (int i = 0; i < n - 1; ++i)
	{
		vector<int> less = dict[i];
		vector<int> more = dict[i + 1];

		int j = 0;
		bool f2 = true;

		while (j < min(less.size(), more.size()))
		{
			if (less[j] > more[j])
			{
				col[less[j]] = 1;
				col[more[j]] = -1;

				f2 = false;

				break;
			}
			else if (less[j] < more[j])
			{
				g[less[j]].push_back(more[j]);
				gr[more[j]].push_back(less[j]);
				f2 = false;

				break;
			}
			else
			{
				g[less[j]].push_back(more[j]);
				gr[more[j]].push_back(less[j]);
			}
			++j;
		}

		if (f2 && less.size() > more.size())
		{
			cout << "No\n";
			return 0;
		}
	}

	for (int i = 0; i <= m; ++i)
	{
		if (!used[i])
		{
			dfs(i);
		}
		if (!used_r[i])
		{
			dfs_r(i);
		}
	}

	if (flag)
	{
		cout << "Yes" << endl;
		vector<int> res;
		for (int i = 0; i < m + 1; ++i)
		{
			if (col[i] == 1)
			{
				res.push_back(i);
			}
		}
		cout << res.size() << endl;
		for (int i = 0; i < res.size(); ++i)
		{
			cout << res[i] << " ";
		}
	}
	else
	{
		cout << "No\n";
	}
	return 0;
}

