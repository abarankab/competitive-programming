// region_d5_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

const int MAXN = 4005;
vector<int> g[MAXN];
vector<int> res;
vector<vector<pair<int, int> > > dp;
int n;

pair<vector<int>, vector<int> > dfs(int v, vector<int> neg, vector<int> pos, int zer = 1, int bal = 0, int pr = -1)
{
	for (int u : g[v])
	{
		if (u < v)
		{
			--bal;
			if (bal < 0)
			{
				if (neg.size() < abs(bal))
				{
					neg.push_back(1);
				}
				else
				{
					++neg[abs(bal) - 1];
				}
				pair<vector<int>, vector<int>> dfs(u, neg, pos, zer, bal, v);
				if (neg.size() < abs(bal))
				{
					neg.pop_back();
				}
				else
				{
					--neg[abs(bal) - 1];
				}
			}
			else if (bal == 0)
			{

			}
			++bal;
		}
	}
}

int main()
{
	cin >> n;
	res.resize(n);
	dp.resize(n);
	for (int i = 0; i < n - 1; ++i)
	{
		dp[i].resize(n);
		int u, v;
		cin >> u >> v;
		--u; --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; ++i)
	{
		vector<int> pos;
		vector<int> neg;
		dfs(i, pos, neg);
	}
    return 0;
}

