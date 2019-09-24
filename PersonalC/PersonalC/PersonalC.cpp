// PersonalC.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>

typedef long double ld;

using namespace std;

struct point
{
	ld x, y;

	point() {}

	point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	point operator-(point B)
	{
		return point(x - B.x, y - B.y);
	}

	ld get_dist()
	{
		return sqrt(x * x + y * y);
	}
};


struct seg
{
	point a, b;
	ld dist;


	seg(point _a, point _b)
	{
		a = _a;
		b = _b;
		dist = (b - a).get_dist();
	}

	seg() {}

	seg normalize()
	{
		return seg(a, point(a.x + (b.x - a.x) / dist, a.y + (b.y - a.y) / dist));
	}
};


int main()
{
	ld x, y;
	cin >> x >> y;
	point A1 = point(x, y);
	cin >> x >> y;
	point B1 = point(x, y);
	cin >> x >> y;
	point A2 = point(x, y);
	cin >> x >> y;
	point B2 = point(x, y);

	seg A = seg(A1, B1);
	seg B = seg(A2, B2);

	seg An = A.normalize();
	seg Bn = B.normalize();

	cout << An.a.x << " " << An.a.y << " " << (An.b.x + An.a.x + (Bn.b.x - Bn.a.x)) / 2 << " " << (An.b.y + An.a.y + (Bn.b.y - Bn.a.y)) << endl;

	cout << 

    return 0;
}

