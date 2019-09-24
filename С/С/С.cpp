// Ñ.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int MAXN = 5000 * 3;
int n, m, len;

set<int> st;
map<int, int> convert;
vector<pair<int, int> > q;
vector<int> need;
int cnt = 0;
vector<vector<int> > sq;

void add(int l, int r)
{
	int low = l / len;
}

int main()
{
	cin >> n >> m;
	len = sqrt(n + .0) + 1;
	st.insert(0);
	st.insert(n + 1);
	sq.resize(len);
	for (int i = 0; i < m; ++i)
	{
		int l, r, g;
		cin >> l >> r >> g;
		st.insert(l);
		st.insert(r);
		st.insert(g);
		q.push_back({ l, r });
		need.push_back(g);
	}
	while (!st.empty())
	{
		int now = *st.begin();
		sq[cnt / len].push_back(0);
		convert[now] = ++cnt;
		st.erase(now);
	}
	for (int i = 0; i < m; ++i)
	{
		q[i].first = convert[q[i].first];
		q[i].second = convert[q[i].second];
		need[i] = convert[need[i]];
	}
	for (int i = 0; i < m; ++i)
	{
		add(1, q[i].first, 0, 1, cnt + 1);
		add(q[i].first, q[i].second + 1, 1, 1, cnt + 1);
		add(q[i].second + 1, convert[n + 1], 0, 1, cnt + 1);
		cout << get(need[i], 1, cnt + 1) << endl;
	}
	return 0;
}

