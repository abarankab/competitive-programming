// M.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e9 + 7;

struct can
{
	long double q, s;
	int ind;

	can() {}
	can(int _q, int _s, int _i)
	{
		q = _q;
		s = _s;
		ind = _i;
	}
};

bool operator<(can a, can b)
{
	if (a.q == b.q)
	{
		return a.ind < b.ind;
	}
	return a.q > b.q;
}

bool cmp(can a, can b)
{
	return a.s * b.q < b.s * a.q;
}

int n, w, res_n = -1, ans;
long double overall_q, res_c = INF;
vector<can> arr;
set<can> st;

signed main()
{
	cin >> n >> w;
	for (int i = 0; i < n; ++i)
	{
		int s, q;
		cin >> s >> q;
		arr.push_back(can(q, s, i));
	}
	sort(arr.begin(), arr.end(), cmp);
	for (int i = 0; i < n; ++i)
	{
		st.insert(arr[i]);
		overall_q += arr[i].q;
		long double max_q = (w * arr[i].q) / arr[i].s;
		while (overall_q > max_q)
		{
			overall_q -= (*st.begin()).q;
			st.erase(st.begin());
		}
		if ((int)st.size() > res_n || ((int)st.size() == res_n && (overall_q * arr[i].s) / arr[i].q < res_c))
		{
			res_n = st.size();
			res_c = (overall_q * arr[i].s) / arr[i].q;
			ans = i;
		}
	}

	st.clear();
	long double max_q = (w * arr[ans].q) / arr[ans].s;
	overall_q = 0;
	for (int i = 0; i <= ans; ++i)
	{
		st.insert(arr[i]);
		overall_q += arr[i].q;
	}
	while (overall_q > max_q)
	{
		overall_q -= (*st.begin()).q;
		st.erase(st.begin());
	}
	cout << st.size() << endl;
	while (!st.empty())
	{
		cout << (*st.begin()).ind + 1 << endl;
		st.erase(st.begin());
	}
	return 0;
}

