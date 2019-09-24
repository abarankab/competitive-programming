// D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

struct sq_raw
{
	int x1, x2, y1, y2;

	sq_raw() {}

	sq_raw(int _x1, int _y1, int _x2, int _y2)
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}
};

struct event
{
	int x, b, t, id;
	bool type;

	event() {}

	event(int _x, int _b, int _t, int _id, bool _type)
	{
		x = _x;
		b = _b;
		t = _t;
		id = _id;
		type = _type;
	}
};

bool operator<(event a, event b)
{
	if (a.x == b.x)
	{
		return a.type < b.type;
	}
	return a.x < b.x;
}

int get(multiset<pair<int, int> > st)
{
	vector<pair<int, int> > arr;
	for (pair<int, int> p : st)
	{
		arr.push_back({ p.first, 0 });
		arr.push_back({ p.second, 1 });
	}
	sort(arr.begin(), arr.end());
	int last = 1, cnt = 0, res = -1;
	for (pair<int, int> p : arr)
	{
		if (cnt == 0)
		{
			res = max(res, p.first - last + 1);
		}

		if (p.second == 0)
		{
			++cnt;
			last = max(p.first, last);
		}
		else
		{
			--cnt;
			last = max(last, p.first + 1);
		}
	}

	return res;
}

int m, n, c, p, ans = -1;
vector<sq_raw> squares;
vector<int> all_x;
unordered_map<int, int> mp;
unordered_map<int, int> mpr;

vector<event> arr;
multiset<pair<int, int> > cur;

int main()
{
	cin >> m >> n >> c >> p;
	for (int i = 0; i < p; ++i)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		squares.push_back(sq_raw(x1, y1, x2, y2));
		all_x.push_back(x1);
		all_x.push_back(x2);
	}

	all_x.push_back(1);
	all_x.push_back(m);

	sort(all_x.begin(), all_x.end());
	unique(all_x.begin(), all_x.end());

	for (int i = 0; i < all_x.size(); ++i)
	{
		mp[i] = all_x[i];
		mpr[all_x[i]] = i;
	}

	for (int i = 0; i < p; ++i)
	{
		arr.push_back(event(mpr[squares[i].x1], squares[i].y1, squares[i].y2, i, 0)); //0 - open
		arr.push_back(event(mpr[squares[i].x2] + 1, squares[i].y1, squares[i].y2, i, 1)); //1 - close
	}

	sort(arr.begin(), arr.end());
	int last = 1;

	for (int i = 0; i < arr.size(); ++i)
	{
		event now = arr[i];

		if (now.type == 1)
		{
			cur.erase(cur.find({ now.b, now.t }));
			
			
		}
		else
		{

		}
	}

    return 0;
}

