// O.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5 * 1e5 + 5;

int n, res;
int arr[MAXN];
int pref[MAXN], check[MAXN];
vector<int> l[MAXN], r[MAXN];

int get(int a, int b)
{
	if (a)
	{
		return pref[b] - pref[a - 1];
	}
	else
	{
		return pref[b];
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
		--arr[i];
		if (arr[i] == i)
		{
			++pref[i];
			check[i] = 1;
		}
		else
		{
			int m = i + arr[i];
			if (m % 2 == 0)
			{
				l[m / 2].push_back(abs((m / 2) - i));
			}
			else
			{
				r[m / 2].push_back((abs(i - arr[i]) / 2) + 1);
			}
		}
		if (i)
		{
			pref[i] += pref[i - 1];
		}
	}
	pair<int, int> ans = { 1, 1 };
	for (int i = 0; i < n; ++i)
	{
		sort(l[i].begin(), l[i].end());
		int cnt = 0;
		for (int now : l[i])
		{
			if ((++cnt) + check[i] - get(i - now, i + now) > res)
			{
				ans = { i - now, i + now };
				res = cnt + check[i] - get(i - now, i + now);
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		sort(r[i].begin(), r[i].end());
		int cnt = 0;
		for (int now : r[i])
		{
			if ((++cnt) - get(i - now + 1, i + now) > res)
			{
				ans = { i - now + 1, i + now };
				res = cnt - get(i - now + 1, i + now);
			}
		}
	}
	cout << arr[ans.first] + 1 << " " << arr[ans.second] + 1 << endl;
    return 0;
}

