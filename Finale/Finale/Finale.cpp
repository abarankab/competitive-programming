// Finale.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <cstring>
#include <queue>

#define int long long
#define next next228
#define prev prev228

typedef long double ld;

using namespace std;

const int N = 505;
const int dx[4] = { 0, 0, 1, -1 };
const int dy[4] = { -1, 1, 0, 0 };

int used[N][N];
bool wall[N][N];
int res[N][N];
int cnt[N][N];
int n, m;

bool on_b(int x, int y)
{
	return (x >= 0 && x < n) && (y >= 0 && y < m);
}

bool deadend(int x, int y)
{
	int cnt = 0;
	for (int move = 0; move < 4; ++move)
	{
		int nx = dx[move] + x;
		int ny = dy[move] + y;

		if (!on_b(nx, ny) || (on_b(nx, ny) && (res[nx][ny] == 0 || res[nx][ny] == 1)))
		{
			++cnt;
		}
	}
	return cnt > 2;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cout.precision(30);

	cin >> n >> m;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char now;
			cin >> now;
			used[i][j] = (now == '#') ? 1 : -1;
			res[i][j] = (now == '.') ? 2 : 0;
		}
	}

	queue<pair<int, int> > q;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (res[i][j] != 0 && deadend(i, j))
			{
				q.push({ i, j });
			}
		}
	}

	while (!q.empty())
	{
		pair<int, int> nw = q.front();
		q.pop();
		res[nw.first][nw.second] = 1;
		for (int move = 0; move < 4; ++move)
		{
			int nx = dx[move] + nw.first;
			int ny = dy[move] + nw.second;

			if (on_b(nx, ny) && res[nx][ny] == 2 && deadend(nx, ny))
			{
				q.push({ nx, ny });
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (res[i][j] == 0)
			{
				cout << '#';
			}
			else if (res[i][j] == 1)
			{
				cout << 'X';
			}
			else
			{
				cout << '.';
			}
		}
		cout << '\n';
	}

	return 0;
}