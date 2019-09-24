// HeavyLight.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <cstring>

using namespace std;

const int MAXN = (int) 1e5 + 228;
const int INF = 1e9 + 7;

int n, k, m;

struct node
{
	int res, l, r;

	vector<pair<int, int> > minl;
	vector<pair<int, int> > minr;

	node()
	{
		res = l = r = INF;
	}

	inline bool is_leaf()
	{
		return (l == r);
	}
};

inline void merge_arrs_l(vector<pair<int, int> > &a, vector<pair<int, int > > &b, vector<pair<int, int> > &c)
{
	int min_pos[51];
	memset(min_pos, INF, sizeof(min_pos));

	for (int i = 0; i < a.size(); ++i)
	{
		min_pos[a[i].second] = min(min_pos[a[i].second], a[i].first);
	}
	for (int i = 0; i < b.size(); ++i)
	{
		min_pos[b[i].second] = min(min_pos[b[i].second], b[i].first);
	}

	int i = 0;
	int j = 0;

	c.clear();

	while (i < a.size() && j < b.size())
	{
		if (a[i].first != min_pos[a[i].second])
		{
			++i;
			continue;
		}

		if (b[j].first != min_pos[b[j].second])
		{
			++j;
			continue;
		}

		if (a[i] < b[j])
		{
			c.push_back(a[i]);
			++i;
		}
		else
		{
			c.push_back(b[j]);
			++j;
		}
	}

	for (int i1 = i; i1 < a.size(); ++i1)
	{
		if (a[i1].first == min_pos[a[i1].second])
		{
			c.push_back(a[i1]);
		}
	}

	for (int j1 = j; j1 < b.size(); ++j1)
	{
		if (b[j1].first == min_pos[b[j1].second])
		{
			c.push_back(b[j1]);
		}
	}
}


inline void merge_arrs_r(vector<pair<int, int> > &a, vector<pair<int, int > > &b, vector<pair<int, int> > &c)
{
	int max_pos[51];
	memset(max_pos, -1, sizeof(max_pos));
	for (int i = 0; i < a.size(); ++i)
	{
		max_pos[a[i].second] = max(a[i].first, max_pos[a[i].second]);
	}
	for (int i = 0; i < b.size(); ++i)
	{
		max_pos[b[i].second] = max(b[i].first, max_pos[b[i].second]);
	}

	int i = 0;
	int j = 0;

	c.clear();

	while (i < a.size() && j < b.size())
	{
		if (a[i].first != max_pos[a[i].second])
		{
			++i;
			continue;
		}
		if (b[j].first != max_pos[b[j].second])
		{
			++j;
			continue;
		}

		if (a[i] < b[j])
		{
			c.push_back(a[i]);
			++i;
		}
		else
		{
			c.push_back(b[j]);
			++j;
		}
	}

	for (int i1 = i; i1 < a.size(); ++i1)
	{
		if (a[i1].first == max_pos[a[i1].second])
		{
			c.push_back(a[i1]);
		}
	}

	for (int j1 = j; j1 < b.size(); ++j1)
	{
		if (b[j1].first == max_pos[b[j1].second])
		{
			c.push_back(b[j1]);
		}
	}
}


inline void solve(vector<pair<int, int> > &a, vector<pair<int, int> > &b, node &c)
{
	int diff = 0;
	vector<int> cnt(k + 1);

	vector<pair<int, int> > over;

	for (int i = 0; i < a.size(); ++i)
	{
		over.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); ++i)
	{
		over.push_back(b[i]);
	}

	int i = 0, j = -1, res = INF;

	while (j + 1 < (int)over.size() || i + 1 < (int)over.size())
	{
		while (j + 1 < (int)over.size() && diff != k)
		{
			++j;
			++cnt[over[j].second];
			if (cnt[over[j].second] == 1)
			{
				++diff;
			}
		}

		if (diff == k)
		{
			res = min(res, over[j].first - over[i].first + 1);
		}

		--cnt[over[i].second];
		if (cnt[over[i].second] == 0)
		{
			--diff;
		}
		++i;
	}

	c.res = min(c.res, res);
}

inline void recount(node &a, node &b, node &c)
{
	c.res = min(a.res, b.res);
	merge_arrs_l(a.minl, b.minl, c.minl);
	merge_arrs_r(b.minr, a.minr, c.minr);

	solve(a.minr, b.minl, c);
}

struct SegmentTree
{
	vector<node> d;

	SegmentTree(int sz)
	{
		d.resize(4 * sz + 5);
	}

	inline void build(int l, int r, int v = 1)
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

	inline void update(int i, int mod, int v = 1)
	{
		if (d[v].is_leaf())
		{
			d[v].minl.clear();
			d[v].minl.push_back({ i, mod });
			d[v].minr.clear();
			d[v].minr.push_back({ i, mod });

			if (k == 1)
			{
				d[v].res = 1;
			}
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
			recount(d[v << 1], d[v << 1 | 1], d[v]);
		}
	}

	inline int get()
	{
		return d[1].res;
	}
};

int main()
{
	ios_base::sync_with_stdio(0);


	cin >> n >> k >> m;

	SegmentTree tree(n);
	tree.build(1, n);

	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		tree.update(i + 1, tmp);
	}

	for (int i = 0; i < m; ++i)
	{
		int type;
		cin >> type;
		if (type == 2)
		{
			if (tree.get() == INF)
			{
				cout << -1 << endl;
			}
			else
			{
				cout << tree.get() << endl;
			}
		}
		else
		{
			int pos, mod;
			cin >> pos >> mod;

			tree.update(pos, mod);
		}
	}

	return 0;
}