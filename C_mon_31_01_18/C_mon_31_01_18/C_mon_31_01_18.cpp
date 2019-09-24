// C_mon_31_01_18.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

char get()
{
	char asd;
	cin >> asd;
	return asd;
}

int main()
{
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<bool> > arr1 (n, vector<bool> (m));
	vector<vector<bool> > arr2 (m, vector<bool>(n));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			bool now = get() == '.';
			arr1[i][j] = now;
			arr2[j][i] = now;
		}
	}

	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		int cur = 0;
		for (int j = 0; j < m; ++j)
		{
			cur = arr1[i][j] ? cur + 1 : 0;
			res += (cur >= k);
		}
	}

	for (int i = 0; i < m; ++i)
	{
		int cur = 0;
		for (int j = 0; j < n; ++j)
		{
			cur = arr2[i][j] ? cur + 1 : 0;
			res += (cur >= k);
		}
	}

	cout << ((k == 1) ? res / 2 : res) << endl;

    return 0;
}

