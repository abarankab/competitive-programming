// region_d2_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

const int MOD = (int)1e9 + 7;

vector<int> dp;
vector<int> last((int)1e6);
vector<int> pref;

int main()
{
	int n;
	cin >> n;
	dp.resize(n);
	last.assign((int)1e6, -1);
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		--tmp;

		if (i == 0)
		{
			dp[i] = 1;
			pref.push_back(1);
			last[tmp] = i;
			continue;
		}

		if (last[tmp] == -1)
		{
			dp[i] = (pref[pref.size() - 1] + 1) % MOD;
			pref.push_back((dp[i] + pref[pref.size() - 1]) % MOD);
			if (dp[i] < 0) dp[i] += MOD;
			if (pref[pref.size() - 1] < 0) pref[pref.size() - 1] += MOD;
			last[tmp] = i;
		}
		else
		{
			dp[i] = (pref[pref.size() - 1] - pref[last[tmp]] + dp[last[tmp]]) % MOD;
			pref.push_back((dp[i] + pref[pref.size() - 1]) % MOD);
			if (dp[i] < 0) dp[i] += MOD;
			if (pref[pref.size() - 1] < 0) pref[pref.size() - 1] += MOD;
			last[tmp] = i;
		}
	}
	cout << pref[pref.size() - 1];
    return 0;
}

