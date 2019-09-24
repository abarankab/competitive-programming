// Day1_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 100005;
const int EXP = 20;

struct edge
{
	int to, val;
	bool clean;

	edge() {}

	edge(int _to, int _val, int _clean)
	{
		to = _to;
		val = _val;
		clean = _clean;
	}
};

struct ret
{
	int ans_q, ans_d;
	int ans_root_q, ans_root_d;
	int sz, sum;
	int sub_clean_d, sub_clean_q;

	ret()
	{
		ans_q = 0;
		ans_d = 0;
	}
};

int n, tm;
vector<edge> g[MAXN];
long double all_dist, all_q;

ret dfs(int v = 0, int pr = 0)
{
	ret now;
	vector<ret> all;

	for (edge u : g[v])
	{
		if (u.to != pr)
		{
			ret cur = dfs(u.to, v);
			now.ans_q += cur.ans_q;
			now.ans_d += cur.ans_d;

			if (!u.clean)
			{
				now.ans_root_q += cur.ans_root_q;
				now.ans_root_d += cur.ans_root_d + cur.ans_root_q * u.val;
				now.sub_clean_d += cur.sub_clean_d;
				now.sub_clean_q += cur.sub_clean_q;
			}
			else
			{
				now.ans_root_q = cur.sz;
				now.ans_root_d = cur.sum + cur.sz * u.val;
				now.sub_clean_d = cur.sz;
				now.sub_clean_q = cur.sum + cur.sz * u.val;
			}

			now.ans_q += now.ans_root_q;
			now.ans_d += now.ans_root_d;
			all.push_back(cur);
		}
	}

	if (all.size() > 1)
	{
		int sub_clean_d = all[0].sub_clean_d + all[0].sub_clean_q * g[v][0].val;
		int sub_clean_q = all[0].sub_clean_q;
		int sz = all[0].sz;

		for (int i = 1; i < all.size(); ++i)
		{
			int d1 = sub_clean_d + sub_clean_q * all[i].sz;
			int d2 = all[i].sub_clean_d + all[i].sub_clean_q * sz;
			int dm = sub_clean_d + sub_clean_q * all[i].sub_clean_d;

			sub_clean_d += d1 + d2 - dm;

			sub_clean_d
		}
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n - 1; ++i)
	{
		int u, v, val, clean;
		cin >> u >> v >> val >> clean;
		--u; --v;
		g[u].push_back(edge(v, val, clean));
		g[v].push_back(edge(u, val, clean));
	}
	dfs();

	cout.precision(20);
	if (!all_q)
	{
		cout << 0 << endl;
		return 0;
	}
	cout << all_dist / all_q << endl;
	return 0;
}

/*
5
1 2 1 1
1 3 4 0
3 4 2 1
3 5 2 0
*/