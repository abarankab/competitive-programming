// B.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = (int)1e5 + 5;

int n, m;
vector<int> site;
set<int> used;
vector<pair<int, int> > arr;
vector<int> res;

struct node
{
	int l, r, val;
};

struct SegmentTree
{
	vector<node> d;

	SegmentTree(vector<int> arr)
	{
		d.resize(arr.size() * 4);
		build(1, arr.size());

		for (int i = 0; i < arr.size(); ++i)
		{
			update(i + 1, arr[i]);
		}
	}

	void build(int l, int r, int v = 1)
	{
		d[v].l = l;
		d[v].r = r;

		if (l == r)
		{
			return;
		}

		int m = (l + r) >> 1;
		build(l, m, v * 2);
		build(m + 1, r, v * 2 + 1);
	}

	void update(int i, int mod, int v = 1)
	{
		if (d[v].l == d[v].r)
		{
			d[v].val = mod;
		}
		else
		{
			int m = (d[v].l + d[v].r) >> 1;
			if (i <= m)
			{
				update(i, mod, v * 2);
			}
			else
			{
				update(i, mod, v * 2 + 1);
			}
			d[v].val = max(d[v * 2].val, d[v * 2 + 1].val);
		}
	}

	int get(int l, int r, int v = 1)
	{
		if (l > r || d[v].l > r || d[v].r < l)
		{
			return -1;
		}
		if (l <= d[v].l && r >= d[v].r)
		{
			return d[v].val;
		}

		return max(get(l, r, v * 2), get(l, r, v * 2 + 1));
	}
};

int main()
{
	cin >> n;
	site.resize(n);
	res.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> site[i];
	}

	int l = 0, r = 0;
	while (l < n)
	{
		if (r < l)
		{
			r = l;
		}
		while (r < n && !used.count(site[r]))
		{
			used.insert(site[r]);
			++r;
		}
		res[l] = used.size();
		used.erase(site[l]);
		++l;
	}

	SegmentTree t = SegmentTree(res);

	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		int lq, rq, ans = -1;
		cin >> lq >> rq;
		--lq; --rq;
		
		int l = lq - 1, r = n;
		while (r - l > 1)
		{
			int mid = (l + r) >> 1;
			if (res[mid] + mid - 1 > rq)
			{
				r = mid;
			}
			else
			{
				l = mid;
			}
		}
		ans = max(ans, rq - r + 1);
		ans = max(ans, t.get(lq + 1, l + 1));
		cout << ans << endl;
	}
    return 0;
}

