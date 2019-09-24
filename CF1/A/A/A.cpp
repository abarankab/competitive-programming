// A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

#define int long long

int n, m, k, l, r, ans = 0;
vector<int> arr, p;
map<int, int> cnt;

void incl()
{
	--cnt[p[l]];
	ans -= cnt[k ^ p[r]];
	++l;
}

void incr()
{
	++r;
	ans += cnt[k ^ p[r]];
	++cnt[p[r]];
}

void decl()
{
	ans += cnt[k ^ p[l]];
	--cnt[p[l]];
	--l;
}

void incl()
{
	--cnt[p[l]];
	ans -= cnt[k ^ p[l]];
	++l;
}

signed main()
{
	cin >> n >> m >> k;
	arr.push_back(0);
	p.push_back(0);
	for (int i = 1; i <= n; ++i)
	{
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
		p[i] = p[i - 1] ^ tmp;
	}
	return 0;
}