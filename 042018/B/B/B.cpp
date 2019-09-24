// B.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define int long long

int n, x, y;
int rg, lf, up, w, xm, ym;
int ql, qr, qu, qd;
const string exm = "examine";
const string ans = "solution";


bool on_board(int x, int y)
{
	return (x >= 1 && x <= n) && (y >= 1 && y <= n);
}


bool get(int x, int y)
{
	if (!on_board(x, y)) //incorrect query
	{
		while (1) {}
	}
	string res;
	cout << exm << " " << x << " " << y << endl;
	cin >> res;
	return res == "true";
}


void answer(int x, int y)
{
	cout << ans << " " << x + (w / 2) << " " << y + (w / 2) << endl;
}


void getborders()
{
	int delta = 1;
	bool flag = 0;
	while (x + delta <= n && !flag) //OK
	{
		flag = !get(x + delta, y);
		if (!flag)
		{
			delta *= 2;
		}
		else
		{
			break;
		}
	}
	if (x + delta > n)
	{
		rg = n;
	}
	else
	{
		rg = x + delta;
	}

	delta = 1;
	flag = 0;
	while (x - delta >= 1 && !flag) //OK
	{
		flag = !get(x - delta, y);
		if (!flag)
		{
			delta *= 2;
		}
		else
		{
			break;
		}
	}
	if (x - delta < 0)
	{
		lf = 1;
	}
	else
	{
		lf = x - delta;
	}

	delta = 1;
	flag = 0;
	while (y + delta <= n && !flag) //OK
	{
		flag = !get(x, y + delta);
		if (!flag)
		{
			delta *= 2;
		}
		else
		{
			break;
		}
	}
	if (y + delta > n)
	{
		up = n;
	}
	else
	{
		up = y + delta;
	}
}


void bins()
{
	int l = x, r = rg;
	while (r - l > 1)
	{
		int m = (l + r) >> 1;
		if (get(m, y)) //flattened
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}
	w = l - x + 1;

	l = x, r = lf;
	while (l - r > 1)
	{
		int m = (l + r) >> 1;
		if (get(m, y)) //flattened
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}
	w += x - l;
	xm = l;

	l = y, r = up;
	while (r - l > 1)
	{
		int m = (l + r) >> 1;
		if (get(x, m)) //flattened
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}

	ym = l - w + 1;
}


void find_center()
{
	for (int i = 0; i < 3; ++i)
	{
		if (on_board(xm + 2 * (i + 1) * w, ym) && get(xm + 2 * (i + 1) * w, ym))
		{
			++qr;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (on_board(xm - 2 * (i + 1) * w, ym) && get(xm - 2 * (i + 1) * w, ym))
		{
			++ql;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (on_board(xm, ym + 2 * (i + 1) * w) && get(xm, ym + 2 * (i + 1) * w))
		{
			++qu;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (on_board(xm, ym - 2 * (i + 1) * w) && get(xm, ym - 2 * (i + 1) * w))
		{
			++qd;
		}
	}

	if ((qu + qd + 1) % 2 == 0)
	{
		int cv, ch;
		cv = -1 + 2 * (qd == 0);
		ch = -1 + 2 * (ql == 0);

		answer(xm + ch * w, ym + cv * w);
	}
	else
	{
		xm -= ql * w * 2;
		ym -= qd * w * 2;

		answer(xm + 2 * w, ym + 2 * w);
	}
}


signed main()
{
	cin >> n >> x >> y;

	getborders();
	bins();
	find_center();

	return 0;
}

