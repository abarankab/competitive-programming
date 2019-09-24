// region_d2_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

struct node
{
	int val, l, r;

	node()
	{
		val = l = r = -1;
	}

	inline bool is_leaf()
	{
		return (l == r);
	}
};

struct SegmentTreeRight
{
	vector<node> d;

	SegmentTreeRight() {}

	SegmentTreeRight(int n)
	{
		d.resize(4 * n);
		build(1, n);
		for (int i = 0; i < n; ++i)
		{
			update(i + 1, -10);
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
		build(l, m, v + v);
		build(m + 1, r, v + v + 1);
	}

	void update(int i, int mod, int v = 1)
	{
		if (d[v].is_leaf())
		{
			d[v].val = mod;
		}
		else
		{
			int m = (d[v].l + d[v].r) >> 1;
			if (i <= m)
			{
				update(i, mod, v << 1);
			}
			else
			{
				update(i, mod, v << 1 | 1);
			}
			d[v].val = max(d[v << 1].val, d[v << 1 | 1].val);
		}
	}

	int get(int l, int r, int v = 1)
	{
		if (l > r || d[v].l > r || d[v].r < l)
		{
			return -10;
		}

		if (l <= d[v].l && r >= d[v].r)
		{
			return d[v].val;
		}

		return max(get(l, r, v << 1), get(l, r, v << 1 | 1));
	}
};

struct SegmentTreeLeft
{
	vector<node> d;

	SegmentTreeLeft() {}

	SegmentTreeLeft(int n)
	{
		d.resize(4 * n);
		build(1, n);
		for (int i = 0; i < n; ++i)
		{
			update(i + 1, (int)1e9);
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
		build(l, m, v + v);
		build(m + 1, r, v + v + 1);
	}

	void update(int i, int mod, int v = 1)
	{
		if (d[v].is_leaf())
		{
			d[v].val = mod;
		}
		else
		{
			int m = (d[v].l + d[v].r) >> 1;
			if (i <= m)
			{
				update(i, mod, v << 1);
			}
			else
			{
				update(i, mod, v << 1 | 1);
			}
			d[v].val = min(d[v << 1].val, d[v << 1 | 1].val);
		}
	}

	int get(int l, int r, int v = 1)
	{
		if (l > r || d[v].l > r || d[v].r < l)
		{
			return (int)1e9;
		}

		if (l <= d[v].l && r >= d[v].r)
		{
			return d[v].val;
		}

		return min(get(l, r, v << 1), get(l, r, v << 1 | 1));
	}
};

vector<int> arr;
vector<int> top;
vector<int> bottom;
vector<int> pos;

signed main()
{
	int n;
	cin >> n;
	pos.resize(n);
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
		top.push_back(0);
		bottom.push_back(0);
		pos[tmp - 1] = i;
	}
	SegmentTreeLeft ltop = SegmentTreeLeft(n);
	SegmentTreeRight rtop = SegmentTreeRight(n);
	SegmentTreeLeft lbot = SegmentTreeLeft(n);
	SegmentTreeRight rbot = SegmentTreeRight(n);
	bool is_top = 1;
	int now = 0;
	while (now < n - 1)
	{
		if (is_top) //top
		{
			int p1 = pos[now];
			int p2 = pos[now + 1];

			if (p2 < p1)
			{
				swap(p2, p1);
			}
			
			if (abs(p1 - p2) != 1)
			{
				int min_l = ltop.get(p1 + 2, p2);
				int max_r = rtop.get(p1 + 2, p2);

				if (min_l > p1 && max_r < p2)
				{
					//ok
				}
				else
				{
					break;
				}
			}

			ltop.update(p2 + 1, p1);
			rtop.update(p1 + 1, p2);
		}
		else //bot
		{
			int p1 = pos[now];
			int p2 = pos[now + 1];

			if (p2 < p1)
			{
				swap(p2, p1);
			}

			if (abs(p1 - p2) != 1)
			{
				int min_l = lbot.get(p1 + 2, p2);
				int max_r = rbot.get(p1 + 2, p2);

				if (min_l > p1 && max_r < p2)
				{
					//ok
				}
				else
				{
					break;
				}
			}

			lbot.update(p2 + 1, p1);
			rbot.update(p1 + 1, p2);
		}
		is_top ^= 1;
		++now;
	}
	cout << now + 1;
    return 0;
}

