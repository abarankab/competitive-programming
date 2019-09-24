// D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int n, ms;
vector<pair<int, int> > init;
vector<int> save;

struct node
{
	int l, r;
	vector<int> arr;
};

struct SegmentTree
{
	vector<node> d;

	SegmentTree() {}

	SegmentTree(vector<pair<int, int> > arr)
	{
		d.resize(4 * arr.size());
		build(1, arr.size());
		update_arr();
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
			d[v].arr.push_back(mod);
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

			d[v].arr.clear();
			merge(d[v * 2].arr.begin(), d[v * 2].arr.end(), d[v * 2 + 1].arr.begin(), d[v * 2 + 1].arr.end(), back_inserter(d[v].arr));
		}
	}

	void update_arr(int v = 1)
	{
		if (d[v].l == d[v].r)
		{
			d[v].arr.push_back(init[d[v].l - 1].second);
		}
		else
		{
			int m = (d[v].l + d[v].r) >> 1;
			update_arr(v * 2);
			update_arr(v * 2 + 1);
			merge(d[v * 2].arr.begin(), d[v * 2].arr.end(), d[v * 2 + 1].arr.begin(), d[v * 2 + 1].arr.end(), back_inserter(d[v].arr));
		}
	}

	int get(int l, int r, int k, int v = 1)
	{
		if (d[v].l == d[v].r)
		{
			return d[v].arr[0];
		}

		auto it_l = lower_bound(d[v * 2].arr.begin(), d[v * 2].arr.end(), l);
		auto it_r = upper_bound(d[v * 2].arr.begin(), d[v * 2].arr.end(), r);
		int delta = (it_r - it_l);
		if (delta >= k)
		{
			return get(l, r, k, v * 2);
		}
		else
		{
			return get(l, r, k - delta, v * 2 + 1);
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(0);

	cin >> n >> ms;
	if (n <= 100 && ms <= 100)
	{	
		vector<int> arr(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> arr[i];
		}
		for (int i = 0; i < ms; ++i)
		{
			int q;
			cin >> q;
			if (q == 1)
			{
				int l, r, x, y;
				cin >> l >> r >> x >> y;
				--l;

				for (int j = l; j < r; ++j)
				{
					arr[j] = (arr[j] == x) ? y : arr[j];
				}
			}
			else
			{
				int l, r, k;
				cin >> l >> r >> k;
				--l; --k;
				vector<int> tmp;

				for (int j = l; j < r; ++j)
				{
					tmp.push_back(arr[j]);
				}

				sort(tmp.begin(), tmp.end());
				cout << tmp[k] << endl;
			}
		}
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			int tmp;
			cin >> tmp;
			init.push_back({ tmp, i + 1 });
			save.push_back(tmp);
		}
		sort(init.begin(), init.end());
		SegmentTree t = SegmentTree(init);
		for (int o = 0; o < ms; ++o)
		{
			int q;
			cin >> q;
			if (q == 2)
			{
				int l, r, k;
				cin >> l >> r >> k;
				cout << save[t.get(l, r, k) - 1] << endl;
			}
			else
			{
				int l, r, x, y;
				cin >> l >> r >> x >> y;
				if (save[l - 1] == x)
				{

				}
			}
		}
	}
    return 0;
}

