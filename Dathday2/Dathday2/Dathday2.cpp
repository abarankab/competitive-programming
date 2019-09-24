// Dathday2.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 1e6 + 228;

int n, root;
int par, tmp;
vector<int> bright;
vector<int> g[MAXN];
int need;
bool flag = false;
int res1;
int res2;

pair<int, vector<int> > dfs(int v)
{
	int sz_now = bright[v];

	if (flag)
	{
		pair<int, vector<int>> asd;
		return asd;
	}

	vector<int> good_ch;
	for (int u : g[v])
	{
		pair<int, vector<int>> resu = dfs(u);
		sz_now += resu.first;
		if (resu.second.size() > 0)
		{
			for (int i = 0; i < resu.second.size(); ++i)
			{
				good_ch.push_back(resu.second[i]);
			}
		}
		if (good_ch.size() > 1)
		{
			break;
		}
	}
	if (good_ch.size() > 1)
	{
		flag = true;
		res1 = good_ch[0] + 1;
		res2 = good_ch[1] + 1;
	}
	else if (good_ch.size() != 0 && sz_now == 2 * need)
	{
		flag = true;
		res1 = good_ch[0] + 1;
		res2 = v + 1;
	}
	if (sz_now == need)
	{
		good_ch.push_back(v);
	}
	return{ sz_now, good_ch };
}

signed main()
{
	cin >> n;
	int sz_root = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> par >> tmp;
		bright.push_back(tmp);
		sz_root += tmp;
		if (par != 0)
		{
			g[par - 1].push_back(i);
		}
		else
		{
			root = i;
		}
	}

	if (sz_root % 3 != 0)
	{
		cout << -1;
		return 0;
	}

	need = sz_root / 3;

	dfs(root);

	if (!flag)
	{
		cout << -1 << "\n";
	}
	else
	{
		cout << res1 << " " << res2;
	}

	return 0;
}

