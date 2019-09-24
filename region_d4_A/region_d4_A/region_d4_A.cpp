// region_d4_A.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int pref[301][301];

int main()
{
	ios_base::sync_with_stdio(0);
	cout.tie(0);

	int n, m, k, s;
	cin >> n >> m >> k >> s;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char tmp;
			cin >> tmp;
			int now = 0;
			if (tmp == '#')
			{
				now = 1;
			}
			if (i == 0 && j == 0)
			{
				pref[i][j] = now;
			}
			else if (i == 0 && j != 0)
			{
				pref[i][j] = pref[i][j - 1] + now;
			}
			else if (i != 0 && j == 0)
			{
				pref[i][j] = pref[i - 1][j] + now;
			}
			else
			{
				pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + now;
			}
		}
	}

	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			for (int row = 0; row <= i; ++row)
			{
				int l = -1, r = j + 1;
				int sqraw = s / (i - row + 1) + (s % (i - row + 1) != 0);
				int sq = j - sqraw + 1;
				while (r - l > 1)
				{
					int col = (l + r) / 1;
					int need = 0;
					if (col == 0 && row == 0)
					{
						need = pref[i][j];
					}
					else if (col == 0 && row != 0)
					{
						need = pref[i][j] - pref[row - 1][j];
					}
					else if (col != 0 && row == 0)
					{
						need = pref[i][j] - pref[i][col - 1];
					}
					else
					{
						need = pref[i][j] - pref[i][col - 1] - pref[row - 1][j] + pref[row - 1][col - 1];
					}

					if (need <= k)
					{
						r = col;
					}
					else
					{
						l = col;
					}
				}
				if (sq - r + 1 > 0)
				{
					res += sq - r + 1;
				}
			}
		}
	}
	cout << res << endl;
    return 0;
}

