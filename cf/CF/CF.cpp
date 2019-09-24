// CF.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <queue>

//#define int long long

using namespace std;

vector<int> win;
queue<int> q;

int exec(char type, int val, int n)
{
	if (type == '|')
	{
		return n |= val;
	}
	if (type == '&')
	{
		return n & val;
	}
	return n ^ val;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cout.precision(20);

	int n;
	cin >> n;
	int low = 0;
	int top = (1 << 10) - 1;
	for (int i = 0; i < n; ++i)
	{
		char type;
		int val;
		cin >> type >> val;
		low = exec(type, val, low);
		top = exec(type, val, top);
	}

	int anda[10];
	int ora[10];
	int xora[10];

	for (int bit = 0; bit < 10; ++bit)
	{
		pair<int, int> now = { low & 1, top & 1 };
		if (now.first == 0 && now.second == 0)
		{
			anda[bit] = 0;
		}
		else
		{
			anda[bit] = 1;
		}

		if (now.first == 1 && now.second == 0)
		{
			xora[bit] = 1;
		}
		else
		{
			xora[bit] = 0;
		}

		if (now.first == 1 && now.second == 1)
		{
			ora[bit] = 1;
		}
		else
		{
			ora[bit] = 0;
		}

		low >>= 1;
		top >>= 1;
	}

	int andres = 0;
	int orres = 0;
	int xorres = 0;
	for (int pos = 0; pos < 10; ++pos)
	{
		andres |= (anda[pos] << pos);
		orres |= (ora[pos] << pos);
		xorres |= (xora[pos] << pos);
	}

	cout << 3 << endl;
	cout << "& " << andres << endl;
	cout << "| " << orres << endl;
	cout << "^ " << xorres << endl;

	return 0;
}

