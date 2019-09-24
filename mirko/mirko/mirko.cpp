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
	int ts, tf, t, n, res, relax;
	cin >> ts >> tf >> t >> n;

	relax = ts + t;

	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		if (ts + (i + 1) * t <= tf && ts + (i + 1) * t - tmp + 1 < relax)
		{
			relax = ts + (i + 1) * t - tmp + 1;
			res = tmp - 1;
		}
	}

	cout << res;

	return 0;
}