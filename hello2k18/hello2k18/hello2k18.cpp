// hello2k18.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

long long dp[30];

signed main()
{
	int n, l;
	cin >> n >> l;
	for (int i = 0; i < n; ++i)
	{
		cin >> dp[i];
		if (i != 0)
		{
			dp[i] = min(dp[i], 2 * dp[i - 1]);
		}
	}
	for (int i = n; i < 30; ++i)
	{
		dp[i] = dp[i - 1] * 2;
	}
	long long res = (long long)1e18;
	int now = l;
	long long nr = 0;
	while (now > 0)
	{
		int d = 0;
		while (1)
		{
			if (1 << (d + 1) <= now)
			{
				++d;
			}
			else
			{
				break;
			}
		}
		now -= (1 << d);
		nr += dp[d];
	}
	res = min(nr, res);
	for (int i = 0; i < 30; ++i)
	{
		int asd = (l >> i) & 1;
		if (asd == 0)
		{
			int now = l >> i;
			now |= 1;
			now <<= i;
			long long nr = 0;
			while (now > 0)
			{
				int d = 0;
				while (1)
				{
					if (1 << (d + 1) <= now)
					{
						++d;
					}
					else
					{
						break;
					}
				}
				now -= (1 << d);
				nr += dp[d];
			}
			res = min(nr, res);
		}
	}
	
	cout << res << endl;
    return 0;
}

