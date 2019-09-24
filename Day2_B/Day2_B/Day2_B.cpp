#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int m, n, offset, power, res, cur = 6;
vector<pair<pair<int, int>, int> > players;
set<pair<pair<int, int>, int> > st;
vector<int> gone, arrived, timer;

int main()
{
	cin >> m >> n;
	for (int i = 0; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;
		players.push_back({ { x, y }, i + 1 });
	}

	sort(players.rbegin(), players.rend());

	for (int i = 0; i < 6; ++i)
	{
		st.insert({ { players[i].first.second, players[i].first.first }, players[i].second });
		power += players[i].first.first;
	}

	for (int i = 0; i < m; ++i)
	{
		++offset;
		res += power;

		if (i == m - 1) break;

		while (st.size() > 0 && (*st.begin()).first.first == offset)
		{
			power -= (*st.begin()).first.second;
			gone.push_back((*st.begin()).second);
			timer.push_back(i + 1);
			st.erase(st.begin());
		}

		while (st.size() < 6 && cur < n)
		{
			st.insert({ { players[cur].first.second + offset, players[cur].first.first }, players[cur].second });
			power += players[cur].first.first;
			arrived.push_back(players[cur].second);
			++cur;
		}
	}
	cout << res << endl;
	for (int i = 0; i < 6; ++i)
	{
		cout << players[i].second << " ";
	}
	cout << endl << gone.size() << endl;
	for (int i = 0; i < gone.size(); ++i)
	{
		cout << timer[i] << " " << gone[i] << " " << arrived[i] << endl;
	}
	return 0;
}

