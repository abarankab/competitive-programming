// Last_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5;
int n, res[MAXN];
vector<int> g[MAXN];

pair<int, int> dfs(int v)
{
	pair<int, int> now = {1, 1};
	for (int u : g[v])
	{
		pair<int, int> to = dfs(u);
		now.first += to.first;
		now.second += to.second + to.first;
	}
	res[v] = now.second;
	return now;
}

signed main()
{
	cin >> n;
	for (int i = 0; i < n - 1; ++i)
	{
		int p;
		cin >> p;
		g[--p].push_back(i + 1);
	}
	dfs(0);
	for (int i = 0; i < n; ++i)
	{
		cout << res[i] << " ";
	}
	cout << "\n";
    return 0;
}

