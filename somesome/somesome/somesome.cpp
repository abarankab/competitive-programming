// somesome.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct team
{
	vector<int> df;
	vector<int> ac;
	vector<int> md;
	int sum;
	bool is_null;

	team()
	{
		sum = 0;
		is_null = 1;
	}

	team(bool _is_null)
	{
		is_null = _is_null;
	}
};

struct player
{
	int d, a, m;

	player() {}

	player(int _dfp, int _acp, int _mdp)
	{
		d = _dfp;
		a = _acp;
		m = _mdp;
	}
};

bool cmp_a(player a, player b)
{
	return a.a < b.a;
}

bool cmp_d(player a, player b)
{
	return a.d < b.d;
}

bool cmp_m(player a, player b)
{
	return a.m < b.m;
}

int n;
vector<player> arr;

int main()
{
	cin >> n;
	
	for (int i = 0; i < n; ++i)
	{
		int d, m, a;
		cin >> d >> m >> a;
		arr.push_back(player(d, m, a));
	}

	sort(arr.begin(), arr.end(), cmp_a);

    return 0;
}

