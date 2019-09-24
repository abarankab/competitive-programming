// Munin.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

typedef long double ld;

const ld EPS = (ld)1e-9;
const ld Pi = 3.14159265359;
const ld INF = (ld)1e9;

struct point
{
	ld x, y;

	point() {}

	point(ld _x, ld _y)
	{
		x = _x;
		y = _y;
	}

	point operator+(point b)
	{
		return point(x + b.x, y + b.y);
	}

	point operator-(point b)
	{
		return point(x - b.x, y - b.y);
	}

	bool operator==(point b)
	{
		return abs(x - b.x) < EPS && abs(y - b.y) < EPS;
	}

	ld operator%(point b)
	{
		return x * b.y - y * b.x;
	}

	ld operator*(point b)
	{
		return x * b.x + y * b.y;
	}

	point median()
	{
		return point(x / 2, y / 2);
	}

	ld dist()
	{
		return sqrt(x * x + y * y);
	}
};

point lower;

ld get_dist(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

ld crossprod(point l, point m, point r)
{
	point v1 = r - m;
	point v2 = l - m;
	return v1 % v2;
}

ld dotprod(point l, point m, point r)
{
	point v1 = r - m;
	point v2 = l - m;
	return v1 * v2;
}

bool polar_deg_cmp(point a, point b)
{
	if (abs(crossprod(a, lower, b)) < EPS)
	{
		return get_dist(a, lower) < get_dist(b, lower);
	}
	return crossprod(a, lower, b) < 0;
}

vector<point> convex_hull(vector<point> arr)
{
	vector<int> preprocess;
	ld min_x = INF;
	ld min_y = INF;
	int min_ind = 0;

	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i].x < min_x)
		{
			min_x = arr[i].x;
			min_ind = i;
		}
		if (arr[i].x == min_x)
		{
			if (arr[i].y < min_y)
			{
				min_y = arr[i].y;
				min_ind = i;
			}
		}
	}
	lower = arr[min_ind];
	sort(arr.begin(), arr.end(), polar_deg_cmp);
	vector<point> res;
	res.push_back(arr[0]);
	int ind = 1;

	while (ind < arr.size())
	{
		if (polar_deg_cmp(res[res.size() - 1], arr[ind]))
		{
			res.push_back(arr[ind]);
			++ind;
		}
		else
		{
			res.pop_back();
		}
	}

	return res;
}

bool on_one_circle(point A, point B, point C, point X)
{
	if (A == B || A == C || A == X || B == C || B == X || C == X)
	{
		return 1;
	}
	vector<point> polygon;
	polygon.push_back(A);
	polygon.push_back(B);
	polygon.push_back(C);
	polygon.push_back(X);
	polygon = convex_hull(polygon);
	if (polygon.size() != 4)
	{
		return 0;
	}
	A = polygon[0];
	B = polygon[1];
	C = polygon[2];
	X = polygon[3];
	return (abs(crossprod(A, B, C) * dotprod(C, X, A) + crossprod(C, X, A) * dotprod(A, B, C)) < EPS);
}

int n;
vector<point> arr;

bool solve(int i1, int i2, int i3)
{
	vector<bool> used(n);
	used.assign(n, 0);
	point A = arr[i1];
	point B = arr[i2];
	point C = arr[i3];

	vector<int> main_circle;
	for (int i = 0; i < n; ++i)
	{
		if (on_one_circle(A, B, C, arr[i]))
		{
			main_circle.push_back(i);
			used[i] = 1;
		}
	}
	vector<int> left;
	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			left.push_back(i);
		}
	}

	if (left.size() == 1) //kostyl'
	{
		for (int i = 0; i < main_circle.size(); ++i)
		{
			cout << main_circle[i] + 1 << " ";
		}
		cout << "\n";
		cout << left[0] + 1 << "\n";
		return 1;
	}
	else if (left.size() == 2) //kostyl'
	{
		for (int i = 0; i < main_circle.size(); ++i)
		{
			cout << main_circle[i] + 1 << " ";
		}
		cout << "\n";
		cout << left[0] + 1 << " " << left[1] + 1 << "\n";
		return 1;
	}

	point P = arr[left[0]];
	point Q = arr[left[1]];
	point R = arr[left[2]];

	vector<int> secondary_circle;

	for (int i = 0; i < n; ++i)
	{
		if (on_one_circle(P, Q, R, arr[i]))
		{
			used[i] = 1;
			secondary_circle.push_back(i);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			return 0;
		}
	}

	for (int i = 0; i < main_circle.size(); ++i)
	{
		cout << main_circle[i] + 1 << " ";
	}
	cout << "\n";
	for (int i = 0; i < secondary_circle.size(); ++i)
	{
		cout << secondary_circle[i] + 1 << " ";
	}
	cout << "\n";
	return 1;
}

signed main()
{
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		ld _x, _y;
		cin >> _x >> _y;
		arr.push_back(point(_x, _y));
	}

	if (n < 5) // kostyl'
	{
		if (n == 4)
		{
			cout << "1 2\n3 4\n";
		}
		else if (n == 3)
		{
			cout << "1 2\n3\n";
		}
		else
		{
			cout << "1\n2\n";
		}
		return 0;
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = i + 1; j < 5; ++j)
		{
			for (int k = j + 1; k < 5; ++k)
			{
				if (solve(i, j, k))
				{
					return 0;
				}
			}
		}
	}

	return 0;
}