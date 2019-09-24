// F.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct man
{
	int a, b, c;
	
	man() {}
	
	man(int _a, int _b, int _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}
};

vector<man> arr;

bool ok(man a, man b)
{
	int cnt = 0;
	cnt += a.a == b.a;
	cnt += a.b == b.b;
	cnt += a.c == b.c;
	return cnt == 1;
}

int main()
{
	int n, res = 0;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		arr.push_back(man(a, b, c));
		for (int j = i - 1; j >= 0; --j)
		{
			if (ok(arr[i], arr[j]))
			{
				++res;
			}
		}
	}
	cout << res;
    return 0;
}

