// Last_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t, n, m;
vector<int> h, v;

signed main()
{
	cin >> t;
	for (int o = 0; o < t; ++o)
	{
		cin >> n >> m;
		v.resize(n);
		h.resize(m);
		for (int i = 0; i < n; ++i)
		{
			cin >> v[i];
		}
		for (int i = 0; i < m; ++i)
		{
			cin >> h[i];
		}
		for (int i = 0; i < n; ++i)
		{
			sort(h.begin(), h.end());
			int j = 0;
			while (j < m && !h[j])
			{
				++j;
			}
			while (j < m && v[i])
			{
				--v[i];
				--h[j];
				++j;
			}
		}

		bool found = false;
		for (int i = 0; i < n; ++i)
		{
			if (v[i]) found = true;
		}
		for (int i = 0; i < m; ++i)
		{
			if (h[i]) found = true;
		}

		cout << !found << endl;

		h.clear();
		v.clear();
	}
	return 0;
}

