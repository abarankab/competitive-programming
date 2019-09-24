// D.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <algorithm>

using namespace std;
#define int long long

bool bad[1000005];
int n, res = 0;

int get(int n)
{
	/*int res = 0;
	while (n != 0)
	{
		n &= (n - 1);
		++res;
	}
	return res;*/
	return __builtin_popcountll(n);
}

signed main()
{
	bad[1] = 1;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		bad[i] = 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (bad[i])
		{
			++res;
		}
		bad[i + get(i)] = 0;
	}
	cout << res << endl;
    return 0;
}

