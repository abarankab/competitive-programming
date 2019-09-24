#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = (int)1e9 + 7;

int n, res;
vector<int> arr, to, l, bond, rx;
vector<pair<int, int> > ev;

signed main()
{
	cin >> n;
	arr.resize(n);
	to.resize(n);
	l.resize(n);
	rx.resize(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}

	vector<pair<int, int> > r;

	for (int i = n - 1; i >= 0; --i)
	{
		while (!r.empty() && r.back().first >= arr[i])
		{
			r.pop_back();
		}

		if (r.empty())
		{
			to[i] = n - 1;
		}
		else
		{
			to[i] = r.back().second - 1;
		}

		r.push_back({ arr[i], i });
	}

	r.clear();
	for (int i = n - 1; i >= 0; --i)
	{
		while (!r.empty() && r.back().first < arr[i])
		{
			r.pop_back();
		}

		if (r.empty())
		{
			rx[i] = INF;
		}
		else
		{
			rx[i] = r.back().second;
		}

		r.push_back({ arr[i], i });
	}

	int ind = 0;
	while (ind < n)
	{
		int go = to[ind];

		while (ind < n && rx[ind] <= go)
		{
			ind = rx[ind];
		}

		++ind;
		++res;
	}

	cout << res << endl;
	return 0;
}