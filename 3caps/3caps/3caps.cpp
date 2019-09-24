// 3caps.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5000;
const int INF = (int) 1e9;

int n, d, res;
int dist[MAXN][MAXN];

int main()
{
	cin >> n >> d;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}
	for (int i = 0; i < n - 1; ++i)
	{
		int u, v;
		cin >> u >> v;

		--u; --v;

		dist[u][v] = 1;
		dist[v][u] = 1;
	}

	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			for (int k = j + 1; k < n; ++k)
			{
				if (dist[i][j] == d && dist[i][k] == d && dist[j][k] == d)
				{
					++res;
				}
			}
		}
	}

	cout << res;
    return 0;
}

