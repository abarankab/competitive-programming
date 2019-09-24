// FootTeam.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct player
{
	int a, d, m, id;

	player() {}

	player(int _a, int _b, int _c)
	{
		d = _a;
		m = _b;
		a = _c;
	}

	int get()
	{
		return a + d + m;
	}
};

bool cmp1(player p, player q)
{
	return p.a < q.a;
}

bool cmp2(player p, player q)
{
	return p.d < q.d;
}

bool cmp3(player p, player q)
{
	return p.m < q.m;
}

istream & operator>> (istream &is, player &a)
{
	int x, y, z;
	is >> x >> y >> z;
	a = player(x, y, z);
	is.clear();
	return is;
}

const int MAXN = 5000010;

vector<player> arr;
vector<player> arr1;
vector<player> arr2;
vector<player> arr3;

bool used[MAXN];

int ans;

vector<int> att;
vector<int> mid;
vector<int> def;
vector<int> attres;
vector<int> midres;
vector<int> defres;

vector<int> arr;

int main()
{
	int n, a, k, b, m;
	cin >> n >> a >> k >> b >> m;

    return 0;
}

