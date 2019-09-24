// S.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 5005;

int n, m, k;
int tp[MAXN], dp[MAXN][MAXN], suff[MAXN][MAXN]; // num pos

int inc(int pos)
{
	return (pos + 1) % n;
}

int get(int l, int r, int pos)
{
	return suff[l][pos] - suff[r][pos];
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
	{
		cin >> tp[i];
	}
	for (int i = 0; i < n; ++i)
	{
		if (tp[i])
		{
			dp[m - 1][i] = 0;
			suff[m - 1][i] = 0;
		}
		else
		{
			dp[m - 1][i] = 1;
			suff[m - 1][i] = 1;
		}
	}
	for (int num = m - 2; num >= 0; --num)
	{
		for (int pos = 0; pos < n; ++pos)
		{
			int l = num + 1, r = min(num + k, m - 1) + 1;
			int sum = get(l, r, inc(pos));
			if (tp[pos] == 1)
			{
				dp[num][pos] = sum >= 1;
			}
			else
			{
				sum = (r - l) - sum;
				if (sum != 0)
				{
					dp[num][pos] = 0;
				}
				else
				{
					dp[num][pos] = 1;
				}
			}
			suff[num][pos] = dp[num][pos] + suff[num + 1][pos];
		}
	}
	for (int pos = 0; pos < n; ++pos)
	{
		cout << dp[0][pos] << " ";
	}
	return 0;
}