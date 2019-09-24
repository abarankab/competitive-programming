// A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#pragma GCC optimize ("Ofast")

using namespace std;

#define int long long

int w, h, n, res;
unordered_set<int> st;
const int dx[5] = { 0, -1, 0, 1, 0 };
const int dy[5] = { 0, 0, -1, 0, 1 };

inline bool on_board(int x, int y)
{
	return (x <= w && x >= 1) && (y <= h && y >= 1);
}

signed main()
{
	ios_base::sync_with_stdio(0);

	cin >> w >> h >> n;
	for (int i = 0; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;

		for (int j = 0; j < 5; ++j)
		{
			int nx = x + dx[j];
			int ny = y + dy[j];

			if (on_board(nx, ny) && !st.count((nx << 32) | ny))
			{
				st.insert((nx << 32) | ny);
				++res;
			}
		}
	}

	if (res == w * h)
	{
		cout << "Yes\n";
	}
	else
	{
		cout << "No\n";
	}
	return 0;
}

