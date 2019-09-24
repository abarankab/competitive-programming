#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;

const ld INF = 1e18;
const int K = 1600;
const int MAXN = 150000;

int n, bs[MAXN], res = -1;
vector<pair<int, int> > g[K];
vector<pair<ld, int> > rb[K];
vector<pair<int, int> > a, b;
bool active[MAXN];

int intersect(pair<ld, ld> l1, pair<ld, ld> l2) {
	return (l1.second - l2.second) / (l2.first - l1.first);
}

signed main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int _a, _b;
		cin >> _a >> _b;
		a.push_back({ _a, i });
		b.push_back({ _b, i });
		bs[i] = _b;
	}
	sort(b.rbegin(), b.rend());
	sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i) {
		int got = a[i].first * (n - i), x = 0;
		for (int j = 0; j < K; ++j) {
			vector<pair<int, int> > v = g[j];
			int id = (*lower_bound(rb[j].begin(), rb[j].end(), x)).second;
			got += g[j][id].first * x + g[j][id].second;
			x += g[j].size();
		}

		if (got > res) res = got;
		
		int id = lower_bound(b.begin(), b.end(), make_pair(bs[i], i)) - b.begin();
		int bucket = id / K;
		int cnt = 0;
		active[id] = 1;

		rb[bucket].clear();
		g[bucket].clear();

		for (int j = bucket * K; j < (bucket + 1) * K; ++j) {
			if (j >= n) break;
			if (active[j]) {
				g[bucket].push_back({ b[j].first, b[j].first * (++cnt) });
			}
		}

		vector<pair<int, int> > st;
		sort(g[bucket].begin(), g[bucket].end());
		rb[bucket].push_back({ INF, 0 });
		st.push_back(g[bucket][0]);

		for (int j = 0; j < g[bucket].size(); ++j) {
			while (st.back().first == g[bucket][j].first || intersect(st.back(), g[bucket][j]) < rb[bucket].back().first) {
				st.pop_back();
			}
			st.push_back(g[bucket][j]);
			rb[bucket].push_back({ intersect(st.back(), g[bucket][j]), j });
		}
		
	}

	cout << res << endl;
	return 0;
}