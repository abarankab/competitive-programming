// Day5_D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 3e5 + 1;
int n, k;
int arr[MAXN];
long double pref[MAXN], mpref[MAXN];

bool check(long double x)
{
	memset(pref, 0, MAXN);
	memset(mpref, 0, MAXN);
	for (int i = 0; i < n; ++i)
	{
		pref[i] = arr[i] - x;
		if (i) pref[i] += pref[i - 1];
		mpref[i] = pref[i];
		if (i) mpref[i] = min(mpref[i - 1], mpref[i]);
	}
	long double res = -1;
	for (int i = 0; i < n; ++i)
	{
		if (i > k)
		{
			res = max(res, pref[i] - mpref[i - k]); //CHECK
		}
	}
	return res > 0;
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}
	long double l = 0, r = 1000000000;
	for (int i = 0; i < 50; ++i)
	{
		long double m = (l + r) / 2;
		if (check(m))
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}
	cout.precision(20);
	cout << fixed << l << endl;
    return 0;
}

