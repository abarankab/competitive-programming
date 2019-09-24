// Day2_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, ans = -1, l, r, all;
vector<int> arr, to;
vector<bool> good; // good :)

int main()
{
	cin >> n;
	arr.resize(n);
	to.resize(2 * n);
	good.resize(2 * n);
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
		--arr[i];
		if (i != arr[i])
		{
			++to[i + arr[i]];
		}
		else
		{
			good[2 * i] = 1;
			++all;
		}
	}
    return 0;
}

