// region_d5_D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > game;
vector<vector<vector<int> > > pos; //cir, col, <positions>
int n, k;

int generate(int sec, int col)
{
	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		int mr = (int)1e5;
		if (pos[i][col].size() == 0)
		{
			return (int)1e5;
		}
		for (int nm = 0; nm < pos[i][col].size(); ++nm)
		{
			mr = min(mr, min(abs(pos[i][col][nm] - sec), k - abs(pos[i][col][nm] - sec)));
		}
		res += mr;
	}
	return res;
}

int main()
{
	cin >> n >> k;
	game.resize(n);
	pos.resize(n);
	for (int i = 0; i < n; ++i)
	{
		pos[i].resize(k);
		game[i].resize(k);
		for (int j = 0; j < k; ++j)
		{
			cin >> game[i][j];
			pos[i][game[i][j] - 1].push_back(j);
		}
	}
	
	int res = (int)1e5;
	for (int i = 0; i < k; ++i)
	{
		for (int col = 0; col < k; ++col)
		{
			res = min(res, generate(i, col));
		}
	}
	if (res == (int)1e5)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << res;
	}
    return 0;
}

