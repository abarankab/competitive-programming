// 11022018.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int MOD = 1791791791;

vector<pair<int, int> > wall;
set<int> waiting;

long long res = 0;

int main()
{
	int n, s;
	cin >> n >> s;
	for (int i = 0; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;
		wall.push_back({ y, x });
		res += (long long)x;
	}
	sort(wall.rbegin(), wall.rend());
	for (int i = 0; i < n; ++i)
	{
		/*
		while (!waiting.empty() && -(*waiting.begin()) > wall[i].first && s > 0)
		{
		--s;
		res += (long long)(*waiting.begin());
		waiting.erase(waiting.begin());
		}

		if (s == 0)
		{
		break;
		}
		*/

		res -= (long long)min(s, wall[i].second / wall[i].first) * (long long)wall[i].first;
		s -= min(s, wall[i].second / wall[i].first);
		if (s == 0)
		{
			break;
		}
		waiting.insert(-(wall[i].second % wall[i].first));
	}

	while (!waiting.empty() && s > 0)
	{
		--s;
		res += (long long)(*waiting.begin());
		waiting.erase(waiting.begin());
	}

	cout << res;
	return 0;
}

