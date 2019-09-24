// CFin.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>

#define int long long
#define next next228
#define prev prev228

typedef long double ld;

using namespace std;

char arr[300][300];
int hash_top[300][300];
int hash_low[300][300];
int degp[300];
int degq[300];
int p = 7;
int q = 13;
int mod = (int) 1e9 + 7;
int n, m;

int res;

int get_top(int i1, int j1, int i2, int j2)
{
	if (i1 == 0 && j1 == 0)
	{
		return hash_top[i2][j2];
	}
	else if (i1 == 0 && j1 != 0)
	{
		int res = hash_top[i2][j2];
		res -= hash_top[i2][j1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		res *= degq[j1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		return res;
	}
	else if (i1 != 0 && j1 == 0)
	{
		int res = hash_top[i2][j2];
		res -= hash_top[i1 - 1][j2];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		res *= degp[i1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		return res;
	}
	else
	{
		int res = hash_top[i2][j2];
		res -= hash_top[i1][j2];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}

		res -= hash_top[i2][j1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}

		res += hash_top[i1 - 1][j1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}

		res *= degp[i1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		res *= degq[j1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		return res;
	}
}

int get_low(int i1, int j1, int i2, int j2)
{
	if (i1 == n - 1 && j1 == m - 1)
	{
		return hash_top[i2][j2];
	}
	else if (i1 == n - 1 && j1 != m - 1)
	{
		int res = hash_top[i2][j2];
		res -= hash_top[i2][j1 + 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		res *= degq[m - j1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		return res;
	}
	else if (i1 != n - 1 && j1 == m - 1)
	{
		int res = hash_top[i2][j2];
		res -= hash_top[i1 + 1][j2];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		res *= degp[n - i1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		return res;
	}
	else
	{
		int res = hash_top[i2][j2];
		res -= hash_top[i1 + 1][j2];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}

		res -= hash_top[i2][j1 + 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}

		res += hash_top[i1 + 1][j1 + 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}

		res *= degp[n - i1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		res *= degq[m -j1 - 1];
		res %= mod;
		if (res < 0)
		{
			res += mod;
		}
		return res;
	}
}


void ok(int i1, int j1, int i2, int j2)
{
	if (get_top(i1, j1, i2, j2) == get_low(i2, j2, i1, j1))
	{
		++res;
	}
}

signed main()
{
	degp[0] = 1;
	degq[0] = 1;
	for (int i = 1; i < 300; ++i)
	{
		degp[i] = (degp[i - 1] * p) % mod;
		if (degp[i] < 0)
		{
			degp[i] += mod;
		}
		degq[i] = (degq[i - 1] * q) % mod;
		if (degq[i] < 0)
		{
			degq[i] += mod;
		}
	}

	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> arr[i][j];
		}
	}

	hash_top[0][0] = (arr[0][0] - 'a' * degq[m - 1]) % mod;
	if (hash_top[0][0] < 0)
	{
		hash_top[0][0] += mod;
	}
	hash_top[0][0] *= degq[m - 1];
	hash_top[0][0] %= mod;
	if (hash_top[0][0] < 0)
	{
		hash_top[0][0] += mod;
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (i != 0 && j != 0)
			{
				hash_top[i][j] = (hash_top[i - 1][j] + hash_top[i][j - 1] - hash_top[i - 1][j - 1] + (arr[i][j] - 'a') * degp[n - i - 1] * degq[m - j - 1]) % mod;
				if (hash_top[i][j] < 0)
				{
					hash_top[i][j] += mod;
				}
			}
			if (i != 0 && j == 0)
			{
				hash_top[i][j] = (hash_top[i - 1][j] + (arr[i][j] - 'a') * degp[n - i - 1] * degq[m - j - 1]) % mod;
				if (hash_top[i][j] < 0)
				{
					hash_top[i][j] += mod;
				}
			}
			if (i == 0 && j != 0)
			{
				hash_top[i][j] = (hash_top[i][j - 1] + (arr[i][j] - 'a') * degp[n - i - 1] * degq[m - j - 1]) % mod;
				if (hash_top[i][j] < 0)
				{
					hash_top[i][j] += mod;
				}
			}
		}
	}


	hash_low[n - 1][m - 1] = arr[n - 1][m - 1] - 'a';

	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = m - 1; j >= 0; --j)
		{
			if (i != n - 1 && j != m - 1)
			{
				hash_low[i][j] = (hash_low[i + 1][j] + hash_low[i][j + 1] - hash_low[i + 1][j + 1] + (arr[i][j] - 'a') * degp[i] * degq[j]) % mod;
				if (hash_low[i][j] < 0)
				{
					hash_low[i][j] += mod;
				}
			}
			if (i != n - 1 && j == m - 1)
			{
				hash_low[i][j] = (hash_low[i + 1][j] + (arr[i][j] - 'a') * degp[i] * degq[j]) % mod;
				if (hash_low[i][j] < 0)
				{
					hash_low[i][j] += mod;
				}
			}
			if (i == n - 1 && j != m - 1)
			{
				hash_low[i][j] = (hash_low[i][j + 1] + (arr[i][j] - 'a') * degp[i] * degq[j]) % mod;
				if (hash_low[i][j] < 0)
				{
					hash_low[i][j] += mod;
				}
			}
		}
	}


	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			for (int i1 = i; i1 < n; ++i1)
			{
				for (int j1 = j; j1 < m; ++j1)
				{
					ok(i, j, i1, j1);
				}
			}
		}
	}

	cout << res;
	return 0;
}

