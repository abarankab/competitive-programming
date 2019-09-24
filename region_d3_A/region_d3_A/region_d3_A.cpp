// region_d3_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

//#define int long long

using namespace std;

struct ant
{
	int x, y;
	int v, ind;

	ant() {}

	ant(int _x, int _y, int _v, int _ind)
	{
		x = _x;
		y = _y;
		v = _v;
		ind = _ind;
	}
};

bool cmph(ant a, ant b)
{
	return a.y < b.y;
}

bool cmpv(ant a, ant b)
{
	return a.x < b.x;
}

vector<vector<ant> > hor;
vector<vector<ant> > ver;
vector<vector<ant> > hor_r;
vector<vector<ant> > ver_r;

int main()
{
	int w, h, k, t;
	cin >> w >> h >> k >> t;
	hor.resize(h);
	ver.resize(w);
	hor_r.resize(h);
	ver_r.resize(w);
	for (int i = 0; i < k; ++i)
	{
		int x, y;
		int v;
		cin >> x >> y >> v;
		if (v % 2 == 0)
		{
			ver[y].push_back(ant(x, y, v, i));
		}
		else
		{
			hor[x].push_back(ant(x, y, v, i));
		}
	}
	for (int i = 0; i < w; ++i)
	{
		//ver
		for (auto a : ver[i])
		{
			int nh = a.y;
			if (a.v == 2)
			{
				nh += t;
				int rev = (nh / (h + 1));
				if (rev % 2 == 0)
				{
					//normal
					ver_r[i].push_back(ant(a.x, nh % (h), 2, a.ind));
				}
				else
				{
					//reversed
					ver_r[i].push_back(ant(a.x, h - (nh % (h)), 4, a.ind));
				}
			}
			else
			{
				nh = h - nh;
				nh += t;
				int rev = (nh / (h + 1));
				if (rev % 2 == 1)
				{
					//normal
					ver_r[i].push_back(ant(a.x, nh % (h), 2, a.ind));
				}
				else
				{
					//reversed
					ver_r[i].push_back(ant(a.x, h - (nh % (h)), 4, a.ind));
				}
			}
		}
	}
	for (int i = 0; i < h; ++i)
	{
		//hor
		for (auto a : hor[i])
		{
			int nh = a.x;
			if (a.v == 1)
			{
				nh += t;
				int rev = (nh / (w + 1));
				if (rev % 2 == 0)
				{
					//normal
					hor_r[i].push_back(ant(nh % (w), a.y, 1, a.ind));
				}
				else
				{
					//reversed
					hor_r[i].push_back(ant(h - nh % (w), a.y, 1, a.ind));
				}
			}
			else
			{
				nh = w - nh;
				nh += t;
				int rev = (nh / (w + 1));
				if (rev % 2 == 1)
				{
					//normal
					hor_r[i].push_back(ant(nh % (w), a.y, 1, a.ind));
				}
				else
				{
					//reversed
					hor_r[i].push_back(ant(h - nh % (w), a.y, 1, a.ind));
				}
			}
		}
	}
	vector<ant> res(k);
	for (int i = 0; i < h; ++i)
	{
		sort(hor_r[i].begin(), hor_r[i].end(), cmph);
		sort(hor[i].begin(), hor[i].end(), cmph);
		for (int j = 0; j < hor[i].size(); ++j)
		{
			res[hor[i][j].ind] = hor_r[i][j];
		}
	}
	for (int i = 0; i < w; ++i)
	{
		sort(ver_r[i].begin(), ver_r[i].end(), cmpv);
		sort(ver[i].begin(), ver[i].end(), cmpv);
		for (int j = 0; j < ver[i].size(); ++j)
		{
			res[ver[i][j].ind] = ver_r[i][j];
		}
	}
	for (auto ant : res)
	{
		if (ant.v == 2 && ant.y == h)
		{
			cout << ant.x << " " << ant.y << " " << 4 << "\n";
		}
		else if (ant.v == 4 && ant.y == 0)
		{
			cout << ant.x << " " << ant.y << " " << 2 << "\n";
		}
		else if (ant.v == 1 && ant.x == w)
		{
			cout << ant.x << " " << ant.y << " " << 3 << "\n";
		}
		else if (ant.v == 3 && ant.x == 0)
		{
			cout << ant.x << " " << ant.y << " " << 1 << "\n";
		}
		else
		{
			cout << ant.x << " " << ant.y << " " << ant.v << "\n";
		}
	}
    return 0;
}

