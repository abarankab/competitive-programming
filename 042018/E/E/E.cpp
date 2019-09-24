// E.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int> > arr(m, vector<int>(n, 0));
	vector<vector<int> > dp1(m, vector<int>(n, 0));
	vector<vector<vector<int> > > dp2(m, vector<vector<int> >(n, vector<int>(k * 2 + 1, 0)));
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == 0 && j == 0)
			{
				dp1[i][j] = arr[i][j];
			}
			else if (i == 0)
			{
				dp1[i][j] = dp1[i][j - 1] + arr[i][j];
			}
			else if (j == 0)
			{
				dp1[i][j] = dp1[i - 1][j] + arr[i][j];
			}
			else
			{
				dp1[i][j] = min(dp1[i][j - 1], dp1[i][j - 1]) + arr[i][j];
			}
		}
	}
	int res = dp1[m - 1][n - 1];

    return 0;
}

