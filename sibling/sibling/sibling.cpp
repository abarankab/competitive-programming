// sibling.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <cmath>

#define ld long double

using namespace std;

int main()
{
	int h = 0, sum = 0;
	cin >> h;
	vector<int> arr(h + 1);
	for (int i = 0; i < h + 1; ++i)
	{
		cin >> arr[i];
		sum += arr[i];
	}
	int brk = -1;
	for (int i = 1; i < h; ++i)
	{
		if (arr[i] > 1 && arr[i + 1] > 1)
		{
			brk = i;
		}
	}
	int cur_h = 0;
	vector<int> g1(sum);
	vector<int> g2(sum);
	int prv = -1, prv2 = -1;
	for (int i = 0; i < sum; ++i)
	{
		if (cur_h == brk + 1)
		{
			if (i - prv == 0)
			{
				g1[i] = prv;
				g2[i] = prv;
			}
			else if (i - prv == 1)
			{
				g1[i] = prv;
				g2[i] = prv2;
			}
			else
			{
				g1[i] = prv;
				g2[i] = prv;
			}
		}
		else
		{
			g1[i] = prv;
			g2[i] = prv;
		}
		--arr[cur_h];
		if (arr[cur_h] == 0)
		{
			++cur_h;
			prv = i;
			if (cur_h == brk + 1)
			{
				prv2 = i - 1;
			}
		}
	}
	if (brk == -1)
	{
		cout << "perfect" << endl;
	}
	else
	{
		cout << "ambiguous" << endl;
		for (int i = 0; i < sum; ++i)
		{
			cout << g1[i] + 1 << " ";
		}
		cout << '\n';
		for (int i = 0; i < sum; ++i)
		{
			cout << g2[i] + 1 << " ";
		}
	}
    return 0;
}

