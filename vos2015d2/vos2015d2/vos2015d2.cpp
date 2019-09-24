// vos2015d2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

#define int long long

signed main()
{
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i)
	{
		int n, a = 0, b = 0, c = 0;
		cin >> n;

		while (n > 2)
		{
			int k = 60;
			while (3 * (1LL << k) > n)
			{
				--k;
			}
			if (3 * ((1LL << k) - 1) < n - 3 * (1LL << k))
			{
				a |= (1LL << (k + 1LL));
				n -= (1LL << (k + 1LL));
			}
			else
			{
				a |= (1LL << k);
				b |= (1LL << k);
				c |= (1LL << k);
				n -= 3 * (1LL << k);
			}
		}

		if (n == 2)
		{
			a |= 1LL;
			b |= 1LL;
		}
		if (n == 1LL)
		{
			a |= 1LL;
		}

		cout << a << " " << b << " " << c << " \n";
	}
    return 0;
}

