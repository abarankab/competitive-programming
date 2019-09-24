// DFin.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<pair<int, int> > arr;
int n;

bool coll(pair<int, int> a, pair<int, int> b)
{
	return a.first <= b.first && a.second >= b.second;
}

bool check_null(int i)
{
	for (int j = 0; j < n; ++j)
	{
		if (j != i && coll(arr[j], arr[i]))
		{
			return 0;
		}
	}
	return 1;
}

bool check(int i, int j)
{
	if (!coll(arr[j], arr[i]))
	{
		return 0;
	}
	for (int k = 0; k < n; ++k)
	{
		if (k != i && k != j && coll(arr[j], arr[k]) && coll(arr[k], arr[i]))
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	ios_base::sync_with_stdio(0);

	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;
		arr.push_back({ x, y });
	}

	for (int i = 0; i < n; ++i)
	{
		int res;
		cin >> res;
		if (res == 0)
		{
			if (check_null(i))
			{
				cout << "OK" << "\n";
			}
			else
			{
				cout << "WA" << "\n";
			}
		}
		else
		{
			if (res - 1 == i)
			{
				cout << "WA" << "\n";
			}
			else if (check(i, res - 1))
			{
				cout << "OK" << "\n";
			}
			else
			{
				cout << "WA" << "\n";
			}
		}
	}
    return 0;
}

