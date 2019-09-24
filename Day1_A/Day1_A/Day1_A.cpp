// Day1_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
/*
struct diff
{
	int d, pos, val;

	diff() {}

	diff(int _d, int _pos,int _val) {
		d = _d;
		pos = _pos;
		val = _val;
	}
};
*/

const int MAXN = 100005;
int n;
vector<int> arr, pr, nxt;
vector<int> f, s;
set<pair<pair<int, int>, pair<int, int> > > st;

int main()
{
	cin >> n;
	arr.resize(2 * n);
	pr.resize(2 * n);
	nxt.resize(2 * n);

	for (int i = 0; i < 2 * n; ++i)
	{
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());
	
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		st.insert({ { arr[i + 1] - arr[i], -arr[i + 1] - arr[i] }, { i, i + 1 } });
	}

	for (int i = 0; i < 2 * n; ++i)
	{
		pr[i] = i - 1;
		nxt[i] = i + 1;
	}

	while (!st.empty())
	{
		pair<pair<int, int>, pair<int, int> > now = *st.begin();
		st.erase(now);

		int x = now.second.first;
		int y = now.second.second;

		f.push_back(arr[y]);
		s.push_back(arr[x]);

		if (pr[x] != -1)
		{
			int l = pr[x], r = x;
			st.erase({ {arr[r] - arr[l], -arr[l] - arr[r]}, { l, r } });
			nxt[pr[x]] = nxt[y];
		}
		if (nxt[y] != 2 * n)
		{
			int l = y, r = nxt[y];
			st.erase({ { arr[r] - arr[l], -arr[l] - arr[r] }, { l, r } });
			pr[nxt[y]] = pr[x];
		}
		if (pr[x] != -1 && nxt[y] != 2 * n)
		{
			int l = pr[x], r = nxt[y];
			st.insert({ { arr[r] - arr[l], -arr[l] - arr[r] }, { l, r } });
		}
	}

	for (auto x : f)
	{
		cout << x << " ";
	}
	cout << endl;
	for (auto x : s)
	{
		cout << x << " ";
	}
    return 0;
}

