// D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long double

int n, k;
vector<int> arr, pref;

signed main()
{
	cin >> n >> k;
	arr.resize(n);
	pref.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
		pref[i] = arr[i];
		if (i)
		{
			pref[i] += pref[i - 1];
		}
	}
	int res = -1;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			if (j - i + 1 >= k)
			{
				int now = pref[j];;
				if (i)
				{
					now -= pref[i - 1];
				}
				res = max(res, now / (j - i + 1));
			}
		}
	}
	cout.precision(20);
	cout << fixed << res << endl;
    return 0;
}

