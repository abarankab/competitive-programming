// Day3_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define int long long

const int MAXN = 40;

int n, k, res, h[MAXN], g[MAXN];
vector<int> dp[MAXN];

signed main()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
	{
		cin >> h[i] >> g[i];
	}
	for (int start = 0; start < n; ++start)
	{
		dp[start].push_back(g[start]);
		for (int nxt = start + 1; nxt < n; ++nxt)
		{
			if (h[nxt] >= h[start])
			{
				for (int val : dp[start])
				{
					dp[nxt].push_back(val + g[nxt]);
				}
			}
		}
		for (int val : dp[start])
		{
			if (val >= k)
			{
				++res;
			}
		}
		dp[start].clear();
	}
	cout << res << endl;
    return 0;
}

