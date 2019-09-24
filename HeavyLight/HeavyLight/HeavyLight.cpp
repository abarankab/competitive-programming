// HeavyLight.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = (int) 1e5 + 228;
const int INF = (int) 1e9 + 7;

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

struct SegmentTree
{
	vector<node> d;

	SegmentTree() {}

	SegmentTree(vector<int> arr)
	{
		d.resize(4 * arr.size());
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
			return 0;
		}

		if (l <= d[v].l && r >= d[v].r)
		{
			return d[v].val;
		}

		return max(get(l, r, v << 1), get(l, r, v << 1 | 1));
	}
};


vector<int> g[MAXN];
int sz[MAXN];
int h[MAXN];
int tin[MAXN];
int tout[MAXN];
int p[MAXN][65];
int root[MAXN];
bool used[MAXN];
map<int, SegmentTree> HeavyLight;
vector<int> current_path;
vector<int> ladder;
int n;

int timer;


void dfs1(int v, int par = 0)
{
	p[v][0] = par;
	for (int k = 1; k <= 64; ++k)
	{
		p[v][k] = p[p[v][k - 1]][k - 1];
	}
	if (v == par)
	{
		h[v] = 0;
	}
	else
	{
		h[v] = h[par] + 1;
	}

	tin[v] = timer++;
	sz[v] = 1;

	for (int i = 0; i < g[v].size(); ++i)
	{
		int u = g[v][i];
		if (u != par)
		{
			dfs1(u, v);
			sz[v] += sz[u];
		}
	}
	tout[v] = timer++;
}


void dfs2(int v, int rt = 0)
{
	used[v] = 1;

	current_path.push_back(ladder[v]);
	root[v] = rt;
	int max_v;
	int max_sz = -1;

	for (int i = 0; i < g[v].size(); ++i)
	{
		int u = g[v][i];
		if (!used[u])
		{
			if (sz[u] > max_sz)
			{
				max_v = u;
				max_sz = sz[u];
			}
		}
	}

	if (max_sz != -1)
	{
		dfs2(max_v, rt);
		for (int i = 0; i < g[v].size(); ++i)
		{
			int u = g[v][i];
			if (u != max_v && !used[u])
			{
				current_path.clear();
				dfs2(u, u);
			}
		}
	}
	else
	{
		HeavyLight[rt] = SegmentTree(current_path);
	}
}


int get_res(int v, int up)
{
	int rt = root[v];
	if (h[rt] <= h[up])
	{
		return HeavyLight[rt].get(h[up] - h[rt] + 1, h[v] - h[rt] + 1);
	}
	else
	{
		return max(HeavyLight[rt].get(1, h[v] - h[rt] + 1), get_res(p[rt][0], up));
	}
}


inline bool parent(int u, int v)
{
	return tin[v] <= tout[u] && tin[v] >= tin[u];
}


int get_lca(int u, int v)
{
	if (parent(u, v)) return u;
	if (parent(v, u)) return v;
	int k = 64;
	while (k >= 0)
	{
		if (!parent(p[v][k], u))
		{
			v = p[v][k];
		}
		--k;
	}
	return p[v][0];
}


int main()
{
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		ladder.push_back(tmp);
	}

	for (int i = 0; i < n - 1; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u;
		--v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs1(0);
	dfs2(0);

	int m;
	cin >> m;

	for (int i = 0; i < m; ++i)
	{
		char tp;
		int a, b;
		cin >> tp >> a >> b;
		if (tp == '?')
		{
			--a, --b;
			int lc = get_lca(a, b);
			cout << max(get_res(a, lc), get_res(b, lc)) << endl;
		}
		else
		{
			--a;
			HeavyLight[root[a]].update(h[a] - h[root[a]] + 1, b);
		}
	}

	return 0;
}