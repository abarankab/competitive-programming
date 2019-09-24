// 11022018.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

vector<pair<int, int> > wall;
multiset<int> waiting;

long long res = 0;

int main()
{
	int n, s;
	cin >> n >> s;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		res += (long long)x;
		if (y <= x) {
			wall.push_back({ y, x });
		}
		else {
			waiting.insert(-x);
		}
	}
	sort(wall.rbegin(), wall.rend());
	for (int i = 0; i < wall.size(); ++i) {
		while (s && !waiting.empty() && -*waiting.begin() >= wall[i].first)
		{
			--s;
			res += *waiting.begin();
			waiting.erase(waiting.begin());
		}

		if (s == 0) break;

		res -= min(s, wall[i].second / wall[i].first) * wall[i].first;
		s -= min(s, wall[i].second / wall[i].first);
		waiting.insert(-(wall[i].second % wall[i].first));
	}

	while (s && !waiting.empty())
	{
		--s;
		res += *waiting.begin();
		waiting.erase(waiting.begin());
	}

	cout << res;
	return 0;
}

