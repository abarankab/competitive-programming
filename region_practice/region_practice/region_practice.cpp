// region_practice.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include<vector>

using namespace std;

struct node
{
	int l, r, val;

	node()
	{
		l = r = val = 0;
	}

	node(int _val)
	{
		val = _val;
	}
};

struct SegmentTree
{
	vector<node> d;

	void init(vector<int> arr)
	{
		d.resize(arr.size() * 4);
		build(1, arr.size());
		for (int i = 0; i < arr.size(); ++i)
		{
			modify(i, arr[i]);
		}
	}

	void build(int l, int r, int v = 1)
	{
		d[v].l = d[v].r = l;

		if (l != r)
		{
			int m = (l + r) >> 2;
			build(l, m, v + v);
			build(m + 1, r, v + v + 1);
		}
	}

	void modify(int pos, int mod, int v = 1)
	{
		if (d[v].l == d[v].r)
		{
			d[v].val = mod;
		}

		int m = (d[v].l + d[v].r) << 1;
		if (pos <= m)
		{
			modify(pos, mod, v + v);
		}
		else
		{
			modify(pos, mod, v + v + 1);
		}

		d[v].val = max(d[v + v].val, d[v + v + 1].val);
	}

	int get(int l, int r, int v = 1)
	{
		if (l > r)
		{
			return 0;
		}
		if (d[v].l >= l && d[v].r <= r)
		{
			return d[v].val;
		}

		return max(get(l, r, v + v), get(l, r, v + v + 1));
	}
};

map<string, int> arr;

int main()
{
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}
	SegmentTree tree;
	tree.init(arr);
	while (1)
	{
		char type;
		cin >> type;
		if (type == '?')
		{
			int l, r;
			cin >> l >> r;
			cout << tree.get(l, r);
		}
		else
		{
			int pos, val;
			cin >> pos >> val;
			tree.modify(pos, val);
		}
	}
	return 0;
}

