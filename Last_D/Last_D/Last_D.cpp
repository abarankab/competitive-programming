// Last_D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

/*
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("enroll-loops")
#pragma GCC optimize ("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
*/

const int LEN = 700;
const int MAXN = 5e5 + 5;

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

int n, k, qr, timer, l, r = -1, sz = 0;
int arr[MAXN];
map<int, int> convert, convert_back;
query q[MAXN];
int cnt[MAXN];
int ans[MAXN];
int pos[MAXN];
vector<int> ex;

void solve()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		if (!convert.count(tmp))
		{
			convert_back[timer] = tmp;
			convert[tmp] = timer++;
		}
		arr[i] = convert[tmp];
	}
	cin >> qr;
	for (int i = 0; i < qr; ++i)
	{
		int ln, rn;
		cin >> ln >> rn;
		q[i] = query(ln - 1, rn - 1, i);
	}
	sort(q, q + qr, cmp);
	for (int i = 0; i < qr; ++i)
	{
		vector<int> to;
		while (r < q[i].r)
		{
			++r;
			if (cnt[arr[r]] == k)
			{
				pos[ex[sz - 1]] = pos[arr[r]];
				ex[pos[arr[r]]] = ex[--sz];
				ex.pop_back();
				pos[arr[r]] = -1;
			}
			++cnt[arr[r]];
			if (cnt[arr[r]] == k)
			{
				pos[arr[r]] = sz++;
				ex.push_back(arr[r]);
			}
		}
		while (l > q[i].l)
		{
			--l;
			if (cnt[arr[l]] == k)
			{
				pos[ex[sz - 1]] = pos[arr[l]];
				ex[pos[arr[l]]] = ex[--sz];
				ex.pop_back();
				pos[arr[l]] = -1;
			}
			++cnt[arr[l]];
			if (cnt[arr[l]] == k)
			{
				pos[arr[l]] = sz++;
				ex.push_back(arr[l]);
			}
		}
		while (r > q[i].r)
		{
			if (cnt[arr[r]] == k)
			{
				pos[ex[sz - 1]] = pos[arr[r]];
				ex[pos[arr[r]]] = ex[--sz];
				ex.pop_back();
				pos[arr[r]] = -1;
			}
			--cnt[arr[r]];
			if (cnt[arr[r]] == k)
			{
				pos[arr[r]] = sz++;
				ex.push_back(arr[r]);
			}
			--r;
		}
		while (l < q[i].l)
		{
			if (cnt[arr[l]] == k)
			{
				pos[ex[sz - 1]] = pos[arr[l]];
				ex[pos[arr[l]]] = ex[--sz];
				ex.pop_back();
				pos[arr[l]] = -1;
			}
			--cnt[arr[l]];
			if (cnt[arr[l]] == k)
			{
				pos[arr[l]] = sz++;
				ex.push_back(arr[l]);
			}
			++l;
		}

		if (ex.size())
		{
			ans[q[i].id] = convert_back[(*ex.begin())];
		}
		else
		{
			ans[q[i].id] = -1;
		}
	}
	for (int i = 0; i < qr; ++i)
	{
		cout << ans[i] << "\n";
	}
}

int main()
{
	solve();
    return 0;
}

/*
6 2
1 4 2 3 2 1
5
1 2
1 3
3 6
1 6
2 4
*/