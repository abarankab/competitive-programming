// Day2_D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

#define int long long

const int MAXN = 2000;
int n, m, g, res;
int field[MAXN][MAXN];
int col[MAXN][MAXN];
int d[MAXN][MAXN];
vector<pair<int, int> > robots;
vector<int> id;
set<int> used;
map<int, int> dist, cnt;

pair<int, int> get(int x, int y)
{
	if (field[x][y] == 0)
	{
		return { x - 1, y};
	}
	else if (field[x][y] == 1)
	{
		return { x, y + 1 };
	}
	else if (field[x][y] == 2)
	{
		return { x + 1, y};
	}
	else
	{
		return { x, y - 1 };
	}
}

void dfs(int x, int y, int num)
{
	if (col[x][y] != -1 && col[x][y] != num)
	{
		id[num] = id[col[x][y]];
		return;
	}
	else if (col[x][y] != -1)
	{
		id[num] = num;
		return;
	}
	
	pair<int, int> np = get(x, y);
	col[x][y] = num;
	dfs(np.first, np.second, num);
	col[x][y] = id[num];
}

void gfs(int x, int y, int num, int now = 0)
{
	if (d[x][y] == -1)
	{
		d[x][y] = now++;
		pair<int, int> np = get(x, y);
		gfs(np.first, np.second, num, now);
	}
	else
	{
		dist[num] = now - d[x][y];
		return;
	}
}

signed main()
{
	cin >> n >> m >> g;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char now;
			cin >> now;
			if (now == 'N')
			{
				robots.push_back({ i, j });
				field[i][j] = 0;
			}
			else if (now == 'W')
			{
				robots.push_back({ i, j });
				field[i][j] = 3;
			}
			else if (now == 'S')
			{
				robots.push_back({ i, j });
				field[i][j] = 2;
			}
			else if (now == 'E')
			{
				robots.push_back({ i, j });
				field[i][j] = 1;
			}
			else if (now == 'n')
			{
				field[i][j] = 0;
			}
			else if (now == 'w')
			{
				field[i][j] = 3;
			}
			else if (now == 's')
			{
				field[i][j] = 2;
			}
			else if (now == 'e')
			{
				field[i][j] = 1;
			}
		}
	}

	id.resize(robots.size(), -1);
	memset(col, -1, MAXN * MAXN);
	memset(d, -1, MAXN * MAXN);

	for (int i = 0; i < robots.size(); ++i)
	{
		int x = robots[i].first;
		int y = robots[i].second;

		dfs(x, y, i);
	}

	for (int i = 0; i < robots.size(); ++i)
	{
		if (!cnt.count(id[i]))
		{
			cnt[id[i]] = 1;
		}
		else
		{
			++cnt[id[i]];
		}
		if (used.count(id[i]) == 0)
		{
			int x = robots[i].first;
			int y = robots[i].second;

			gfs(x, y, id[i]);
			used.insert(id[i]);
		}
	}
	used.clear();
	for (int i = 0; i < robots.size(); ++i)
	{
		if (!used.count(id[i]))
		{
			res += min(cnt[id[i]], dist[id[i]]);
			used.insert(id[i]);
		}
	}
	cout << res << endl;
    return 0;
}

