// V.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5000;

int n, m, k;
int arr[MAXN], dp[MAXN][MAXN], xr[MAXN], help[MAXN][MAXN];

int get(int l, int r)
{
	int res = xr[r];
	if (l) res ^= xr[l - 1];
	return res;
}

signed main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}
	for (int i = 0; i < n; ++i)
	{
		xr[i] = arr[i];
		if (i) xr[i] ^= xr[i - 1];
	}
	for (int i = 0; i < n; ++i)
	{
		help[i][i] = (arr[i] == k);
		for (int j = i - 1; j >= 0; --j)
		{
			help[i][j] = help[i][j + 1] + (get(j, i) == k);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		dp[i][i] = (arr[i] == k);
		for (int j = i + 1; j < n; ++j)
		{
			dp[i][j] = dp[i][j - 1] + help[j][i];
		}
	}
	for (int i = 0; i < m; ++i)
	{
		int l, r;
		cin >> l >> r;
		--l; --r;
		cout << dp[l][r] << endl;
	}
	return 0;
}

/*
8 4
1 2
1 3
1 4
3 5
3 3
3 7
3 8
*/