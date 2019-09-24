// mirko.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define int long long

using namespace std;

vector<int> l;
vector<int> r;

signed main()
{
	int ts, tf, t, n, res, relax, last;
	cin >> ts >> tf >> t >> n;

	relax = 1e12 + 228;
	last = ts;

	for (int i = 0; i < n; ++i)
	{
		int tmp, now;
		cin >> tmp;
		now = min(last, tmp - 1);

		if (last - now <= relax)
		{
			relax = last - now;
			res = now;
		}

		last = max(last, tmp) + t;

		if (last >= tf)
		{
			break;
		}
	}

	if (last + t <= tf)
	{
		res = last;
	}

	cout << res;
	return 0;
}

