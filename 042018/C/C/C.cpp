// C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int xa, ya, xb, yb, n;

struct point
{
	int x, y;

	point() {}

	point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

int cnt = 0;
unordered_map<int, int> xs, ys, xr, yr;
vector<pair<point, point>> poly;

void add(unordered_map<int, int> &mp, unordered_map<int, int> &mpr, int &to)
{
	if (mp.count(to) == 0)
	{
		mpr[cnt] = to;
		mp[to] = cnt++; 
	}
	to = mp[to];
}

int main()
{
	ios_base::sync_with_stdio(0);

	cin >> xa >> ya >> xb >> yb >> n;
	add(xs, xr, xa);
	add(xs, xr, xb);
	add(ys, yr, ya);
	add(ys, yr, yb);
	for (int i = 0; i < n; ++i)
	{
		int x1, y1, x2, y2, t;
		cin >> x1 >> y1 >> x2 >> y2 >> t;
		add(xs, xr, x1);
		add(xs, xr, x2);
		add(ys, yr, y1);
		add(ys, yr, y2);
		poly.push_back({ point(x1, y1), point(x2, y2) });
	}



    return 0;
}

