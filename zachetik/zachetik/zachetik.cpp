// Munin.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <fstream>

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

	point normal()
	{
		ld d = dist();
		return point(x / d, y / d);
	}

	point operator-()
	{
		return point(-x, -y);
	}

	point operator*(ld mod)
	{
		return point(x * mod, y * mod);
	}
};

struct line
{
	ld a, b, c;

	line(ld _a, ld _b, ld _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}

	line(point p, point q)
	{
		a = p.y - q.y;
		b = q.x - p.x;
		c = -a * p.x - b * p.y;
	}

	line() {}

	ld point_dist(point p)
	{
		return abs((p.x * a + p.y * b + c) / sqrt(a * a + b * b));
	}

	ld point_dist_2(point p)
	{
		return abs((p.x * a + p.y * b + c) / (a * a + b * b));
	}

	point normal_vector()
	{
		return point(a, b);
	}

	bool on_line(point p)
	{
		return abs(a * p.x + b * p.y + c) < EPS;
	}
};

istream &operator >> (istream &is, point &p)
{
	ld _x, _y;
	is >> _x >> _y;
	p = point(_x, _y);
	is.clear();
	return is;
}

ostream &operator << (ostream &os, point &p)
{
	os << p.x << " " << p.y;
	os.clear();
	return os;
}

istream &operator >> (istream &is, line &ln)
{
	ld _a, _b, _c;
	is >> _a >> _b >> _c;
	ln = line(_a, _b, _c);
	is.clear();
	return is;
}

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

bool linear_intersection(point x, point a, point b)
{
	if (a.x > b.x) swap(a, b);
	return (x.x >= a.x && x.x <= b.x) && (x.y >= min(a.y, b.y) && x.y <= max(b.y, a.y));
}

ld a, b, c;
line ln;
point s, f;

point get_by_y(ld y) {
	ld x = -ln.c / ln.a - ln.b / ln.a * y;
	return point(x, y);
}

point get_by_x(ld x) {
	ld y = -ln.c / ln.b - ln.a / ln.b * x;
	return point(x, y);
}

ld get(point a, point b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

signed main()
{
	cout.precision(30);

	cin >> a >> b >> c;
	ln = line(a, b, c);
	cin >> s >> f;

	if (b == 0 || a == 0) {
		cout << get(s, f) << endl;
	}
	else {
		ld res = get(s, f);
		point v = point(a, b);
		v = v.normal();

		if (ln.point_dist(s + v * (ld)1e15) - ln.point_dist(s - v * (ld)1e15) > EPS) {
			v = -v;
		}

		v = v * ln.point_dist(s);

		vector<point> p1;

		for (int d = -100; d <= 100; ++d) {
			p1.push_back(get_by_x((long long)v.x + d));
			p1.push_back(get_by_y((long long)v.y + d));
		}

		v = point(a, b);
		v = v.normal();

		if (ln.point_dist(f + v * (ld)1e15) - ln.point_dist(f - v * (ld)1e15) > EPS) {
			v = -v;
		}

		v = v * ln.point_dist(f);

		vector<point> p2;
		for (int d = -100; d <= 100; ++d) {
			p2.push_back(get_by_x((long long)v.x + d));
			p2.push_back(get_by_y((long long)v.y + d));
		}

		for (point r : p1) {
			for (point g : p2) {
				res = min(res, get(s, r) + get(f, g) + (r - g).dist());
			}
		}

		cout.precision(20);
		cout << res << endl;
	}

	return 0;
}