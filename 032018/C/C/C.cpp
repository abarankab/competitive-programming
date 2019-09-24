// C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <random>

using namespace std;

#define int long double
#define nul ((long double)0)

int l, n;
const int EPS = 1e-6;

struct point
{
	int x, y;

	point() {}
	point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	int operator%(point b)
	{
		return x * b.y - y * b.x;
	}

	point operator-(point b)
	{
		return point(x - b.x, y - b.y);
	}

	int dist()
	{
		return sqrt(x * x + y * y);
	}
};

struct line
{
	long double a, b, c;

	line(point p, point q)
	{
		a = q.y - p.y;
		b = p.x - q.y;
		c = -(a * p.x + b * p.y);
	}
};

signed main()
{
	cin >> l >> n;
	int x1, y1, x2, y2;
	vector<line> arr;
	for (int i = 0; i < n; ++i)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
		point v = point(x2, y2) - point(x1, y1);
		int delta_y = 50 * v.dist() / v.x + EPS;
		int delta_x = EPS;
		if (y1 < y2)
		{
			delta_x = -delta_x;
		}
		arr.push_back(line(point(x1 - delta_x, y1 - delta_y), point(x2 - delta_x, y2 - delta_y)));
		arr.push_back(line(point(x1 + delta_x, y1 + delta_y), point(x2 + delta_x, y2 + delta_y)));
	}

    return 0;
}

