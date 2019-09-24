// region_d32_D.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> travel;
vector<vector<int> > dep;
vector<vector<int> > ret;
vector<vector<vector<int> > > p;

int main()
{
	cin >> n >> m;
	travel.resize(n - 1);
	for (int i = 0; i < n - 1; ++i)
	{
		cin >> travel[i];
	}

	dep.resize(n);
	ret.resize(n);
	p.resize(n);

	for (int i = 0; i < n; ++i)
	{
		p[i].resize(m);
		for (int j = 0; j < m; ++j)
		{
			p[i][j].resize(20);
			p[i][j].assign(20, -1);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		ret[i].resize(m);
		dep[i].resize(m);
		for (int j = 0; j < m; ++j)
		{
			cin >> dep[i][j];
		}
	}

	//count
	for (int i = 0; i < n - 1; ++i)
	{
		ret[i][m - 1] = 0;
		for (int j = m - 2; j >= 0; --j)
		{
			if (travel[i] + dep[i][j + 1] - dep[i][j] <= dep[i + 1][j] - dep[i][j]) //good
			{
				ret[i][j] = ret[i][j + 1] + 1;
			}
			else
			{
				ret[i][j] = 0;
			}
		}
	}

	int asd;
	cin >> asd;

	int q;
	cin >> q;

	for (int bus = 0; bus < m; ++bus)
	{
		for (int i = 0; i <= 19; ++i)
		{
			p[n - 1][bus][i] = bus;
		}
	}

	for (int col = n - 2; col >= 0; --col)
	{
		for (int bus = 0; bus < m; ++bus)
		{
			int par = bus + ret[col][bus];
			p[col][bus][0] = par;

			for (int k = 1; k <= 19; ++k)
			{
				int kbus = p[col][bus][k - 1];
				if (kbus == -1)
				{
					break;
				}
				p[col][bus][k] = p[min(col + k, n - 1)][kbus][k - 1];
			}
		}
	}

	for (int asdf = 0; asdf < q; ++asdf)
	{
		int s, f, bus;
		cin >> s >> f >> bus;
		--s; --f; --bus;

		int k = 19;
		while (k >= 0)
		{
			if (p[s][bus][k] != -1 && s + (1 << k) <= f)
			{
				bus = p[s][bus][k];
				s += (1 << k);
			}
			--k;
		}
		cout << dep[f][bus] << endl;
	}

    return 0;
}

