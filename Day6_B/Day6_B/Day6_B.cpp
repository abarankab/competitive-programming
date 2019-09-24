// Day6_B.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

struct query
{
	int l, r, id;

	query() {}

	query(int _l, int _r, int _id)
	{
		l = _l;
		r = _r;
		id = _id;
	}
};

const int MAXN = 100010, LEN = 370;
int n, m, k, l, r = -1, ans, res[MAXN];
vector<int> p, arr;
int cnt[1<<21];
vector<query> q;

bool const cmp(query a, query b)
{
	if (a.id == b.id)
	{
		return false;
	}
	int bucket_a = a.l / LEN, bucket_b = b.l / LEN;
	if (bucket_a != bucket_b)
	{
		return bucket_a < bucket_b;
	}
	if (bucket_a % 2)
	{
		return a.r < b.r;
	}
	else
	{
		return a.r > b.r;
	}
}

void incr()
{
	++r;
	ans += cnt[p[r] ^ k];
	++cnt[p[r]];
}

void incl()
{
	--cnt[p[l]];
	ans -= cnt[p[l] ^ k];
	++l;
}

void decr()
{
	--cnt[p[r]];
	ans -= cnt[p[r] ^ k];
	--r;
}

void decl()
{
	--l;
	ans += cnt[p[l] ^ k];
	++cnt[p[l]];
}

signed main()
{
	cin >> n >> m >> k;
	p.push_back(0);
	for (int i = 1; i <= n; ++i)
	{
		int tmp;
		cin >> tmp;
		p.push_back(tmp ^ p[i - 1]);
	}
	for (int i = 0; i < m; ++i)
	{
		int l, r;
		cin >> l >> r;
		q.push_back(query(l - 1, r, i));
	}
	sort(q.begin(), q.end(), cmp);
	for (int i = 0; i < m; ++i)
	{
		while (r < q[i].r)
		{
			incr();
		}
		while (l > q[i].l)
		{
			decl();
		}
		while (r > q[i].r)
		{
			decr();
		}
		while (l < q[i].l)
		{
			incl();
		}
		res[q[i].id] = ans;
	}
	for (int i = 0; i < m; ++i)
	{
		cout << res[i] << endl;
	}
	return 0;
}

