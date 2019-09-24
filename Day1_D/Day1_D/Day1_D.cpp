// Day1_D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
long double w, spent;
vector<long double> s;
vector<long double> q;

int main()
{
	cin >> n >> w;
	s.resize(n);
	q.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> s[i] >> q[i];
	}

	long double spent;
	vector<int> res;

	for (int i = 0; i < n; ++i)
	{
		vector<int> cur;
		vector<pair<long double, int> > all;
		long double cost = 0;
		for (int j = 0; j < n; ++j)
		{
			if (s[j] <= q[j] / q[i] * s[i])
			{
				all.push_back({ q[j] / q[i] * s[i] , j });
			}
		}
		sort(all.begin(), all.end());
		int pos = 0;
		while (pos < all.size())
		{
			if (cost + all[pos].first <= w)
			{
				cur.push_back(all[pos].second);
				cost += all[pos].first;
			}
			else
			{
				break;
			}
			++pos;
		}

		if (cur.size() > res.size())
		{
			res = cur;
			spent = cost;
		}
		else if (cur.size() == res.size() && cost < spent)
		{
			res = cur;
			spent = cost;
		}
	}

	cout << res.size() << "\n";
	for (auto x : res)
	{
		cout << x + 1 << "\n";
	}
    return 0;
}

