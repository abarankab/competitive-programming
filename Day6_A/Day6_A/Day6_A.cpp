// Day6_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 105;
int n, m, k, res = MAXN;

vector<int> order[MAXN];
set<int> now;

void gen(int pos = 0)
{
	if (pos == m)
	{
		vector<int> cnt(m);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (!now.count(order[i][j]))
				{
					cnt[order[i][j]]++;
					break;
				}
			}
		}
		for (int i = 0; i < m; ++i)
		{
			if (i != k && make_pair(cnt[i], -i) > make_pair(cnt[k], -k))
			{
				return;
			}
		}
		res = min(res, (int)now.size());
		return;
	}
	now.insert(pos);
	gen(pos + 1);
	now.erase(pos);
	gen(pos + 1);
}

int main()
{
	cin >> n >> m >> k;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			int tmp;
			cin >> tmp;
			order[i].push_back(tmp - 1);
		}
	}
	vector<int> qq(m);
	for (int i = 0; i < n; ++i)
	{
		++qq[order[i][0]];
	}
	int mx = -1, id = 0;
	for (int i = 0; i < m; ++i)
	{
		if (qq[i] > mx)
		{
			mx = qq[i];
			id = i;
		}
	}
	cout << id + 1 << endl;
	gen();
	cout << res << endl;
    return 0;
}

