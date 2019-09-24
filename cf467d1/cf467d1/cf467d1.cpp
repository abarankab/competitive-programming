// cf467d1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <bitset>
#include <map>
#include <algorithm>

using namespace std;

typedef long double ld;
typedef long long ll;

const ll MOD = 1791791791;

#define int long long

struct node
{
	node *l, *r;
	int cnt;

	node() {
		cnt = 0;
		l = nullptr;
		r = nullptr;
	}
};

node *t = new node;

void add(int a)
{
	node *now = t;
	for (int k = 30; k >= 0; --k)
	{
		++now->cnt;
		if (((a >> k) & 1) != 0)
		{
			if (now->r == nullptr)
			{
				now->r = new node;
			}
			now = now->r;
		}
		else
		{
			if (now->l == nullptr)
			{
				now->l = new node;
			}
			now = now->l;
		}
	}

	++now->cnt;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	
	int n;
	cin >> n;

	vector<int> arr;

	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}

	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;

		add(tmp);
	}

	for (auto a : arr)
	{
		int res = 0;
		node *now = t;
		for (int k = 30; k >= 0; --k)
		{
			--now->cnt;
			if (((a >> k) & 1) == 0)
			{
				if (now->l != nullptr && now->l->cnt)
				{
					now = now->l;
				}
				else
				{
					now = now->r;
					res += (1LL << k);
				}
			}
			else
			{
				if (now->r != nullptr && now->r->cnt)
				{
					now = now->r;
				}
				else
				{
					now = now->l;
					res += (1LL << k);
				}
			}
			if (k == 0)
			{
				--now->cnt;
			}
		}
		cout << res << " ";
	}

    return 0;
}

