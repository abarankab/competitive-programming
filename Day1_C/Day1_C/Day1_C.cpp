// Day1_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#define int long double

using namespace std;

const int pi = 3.14159265359;

signed main()
{
	int ox, oy, rd, d1, d2;
	int px, py;
	int s1x, s1y, s2x, s2y;
	cin >> ox >> oy >> rd >> d1 >> d2 >> px >> py >> s1x >> s1y >> s2x >> s2y;

	int sq_d = (ox - px) * (ox - px) + (oy - py) * (oy - py);
	
	if (sq_d < rd * rd)
	{
		if ((s1x - ox) * (s1x - ox) + (s1y - oy) * (s1y - oy) < rd * rd)
		{
			if ((s2x - ox) * (s2x - ox) + (s2y - oy) * (s2y - oy) < rd * rd)
			{
				
			}
		}
		cout << 1 << endl;
	}
	else
	{
		int sq_l = sq_d - rd * rd;
		int l = 0, r = pi;
		for (int w = 0; w < 1000; ++w)
		{
			int m = l + ((r - l) / 2);
			int sq_now = rd * rd + sq_d - 2 * cos(m) * rd * sqrt(sq_d);
			if (sq_now > sq_l)
			{
				r = m;
			}
			else
			{
				l = m;
			}
		}
		l = l / pi;
		cout << min(l / (abs(d1 - d2) / 360), (long double)1) << endl;
	}
    return 0;
}

