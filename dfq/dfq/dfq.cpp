// region_d1_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n, k, res;

struct qr
{
	int w, l, r, h;
	bool rev;

	qr() {}

	qr(int _l, int _r, int _h, bool _rev)
	{
		l = _l;
		r = _r;
		h = _h;
		rev = _rev;
		w = abs(l - r) + 1;
		if (rev)
		{
			w = n - w + 2;
		}
	}
};

bool operator<(qr a, qr b)
{
	if (a.w == b.w)
	{
		return a.l < b.l;
	}
	return a.w < b.w;
}

vector<int> arr;
vector<int> ls;
vector<int> rs;
set<qr> query;

int add(int pos, int mod)
{
	int nw = pos + mod;
	if (nw >= n)
	{
		nw -= n;
	}
	if (nw < 0)
	{
		nw += n;
	}
	return nw;
}

bool good(int hm, int hl, int hr)
{
	return hm < min(hl, hr);
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}

	ls.resize(n);
	rs.resize(n);

	ls[0] = 0;
	rs[n - 1] = n - 1;

	for (int i = 0; i < n; ++i)
	{
		if (i != 0)
		{
			if (arr[i] == arr[i - 1])
			{
				ls[i] = ls[i - 1];
			}
			else
			{
				ls[i] = i;
			}
		}
	}

	for (int i = n - 1; i >= 0; --i)
	{
		if (i < n - 1)
		{
			if (arr[i] == arr[i + 1])
			{
				rs[i] = rs[i + 1];
			}
			else
			{
				rs[i] = i;
			}
		}
	}

	if (arr[0] == arr[n - 1])
	{
		ls[0] = ls[n - 1];
		rs[n - 1] = rs[0];
	}

	for (int i = 0; i < n; ++i)
	{
		if (i != 0)
		{
			if (arr[i] == arr[i - 1])
			{
				ls[i] = ls[i - 1];
			}
			else
			{
				ls[i] = i;
			}
		}
	}

	for (int i = n - 1; i >= 0; --i)
	{
		if (i < n - 1)
		{
			if (arr[i] == arr[i + 1])
			{
				rs[i] = rs[i + 1];
			}
			else
			{
				rs[i] = i;
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		int cur_l = ls[i];
		int cur_r = rs[i];
		if (good(arr[i], arr[add(cur_l, -1)], arr[add(cur_r, 1)]))
		{
			query.insert(qr(cur_l, cur_r, arr[i], cur_l > cur_r)); //TODO
		}
	}

	while (!query.empty())
	{
		qr cur = *query.begin();
		if (cur.w == n)
		{
			break;
		}
		query.erase(cur);
		if (ls[cur.r] != cur.l || rs[cur.l] != cur.r)
		{
			continue;
		}

		int l = add(cur.l, -1);
		int r = add(cur.r, 1);

		int max_h = min(arr[l], arr[r]) - cur.h;
		int added = min(max_h, k / cur.w);
		arr[cur.l] += added;
		if (cur.l != cur.r)
		{
			arr[cur.r] += added;
		}
		k -= cur.w * added;
		res += added * 2;
		if (k < cur.w || l == r)
		{
			break;
		}

		if (arr[l] == min(arr[l], arr[r]) && arr[r] == arr[l])
		{
			int cur_l = ls[l];
			int cur_r = rs[r];
			rs[cur_l] = cur_r;
			ls[cur_r] = cur_l;

			qr to;
			if (cur.rev)
			{
				to = qr(cur_l, cur_r, arr[cur_l], 1);
			}
			else
			{
				if (cur_l > cur_r)
				{
					to = qr(cur_l, cur_r, arr[cur_l], 1);
				}
				else
				{
					to = qr(cur_l, cur_r, arr[cur_l], 0);
				}
			}

			if (good(to.h, arr[add(to.l, -1)], arr[add(to.r, 1)]))
			{
				query.insert(to);
			}
		}
		else if (arr[l] == min(arr[l], arr[r]))
		{
			int cur_l = ls[l];
			int cur_r = cur.r;
			rs[cur_l] = cur_r;
			ls[cur_r] = cur_l;

			qr to;
			if (cur.rev)
			{
				to = qr(cur_l, cur_r, arr[cur_l], 1);
			}
			else
			{
				if (cur_l > cur_r)
				{
					to = qr(cur_l, cur_r, arr[cur_l], 1);
				}
				else
				{
					to = qr(cur_l, cur_r, arr[cur_l], 0);
				}
			}

			if (good(to.h, arr[add(to.l, -1)], arr[add(to.r, 1)]))
			{
				query.insert(to);
			}
		}
		else
		{
			int cur_l = cur.l;
			int cur_r = rs[r];
			rs[cur_l] = cur_r;
			ls[cur_r] = cur_l;

			qr to;
			if (cur.rev)
			{
				to = qr(cur_l, cur_r, arr[cur_l], 1);
			}
			else
			{
				if (cur_l > cur_r)
				{
					to = qr(cur_l, cur_r, arr[cur_l], 1);
				}
				else
				{
					to = qr(cur_l, cur_r, arr[cur_l], 0);
				}
			}

			if (good(to.h, arr[add(to.l, -1)], arr[add(to.r, 1)]))
			{
				query.insert(to);
			}
		}
	}

	cout << res << endl;
	return 0;
}
