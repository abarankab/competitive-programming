#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long double ld;

const ld INF = 1e18;
const int K = 450;
const int MAXN = 150000;

int n, bid[MAXN];
long long res = 0;
vector<pair<long long, long long> > g[K];
vector<pair<ld, int> > rb[K];
int it[K];
pair<long long, int> a[MAXN], b[MAXN];
bool active[MAXN];

ld intersect(pair<ld, ld> l1, pair<ld, ld> l2) {
	return (l1.second - l2.second) / (l2.first - l1.first);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		long long _a, _b;
		cin >> _a >> _b;
		a[i] = { _a, i };
		b[i] = { _b, i };
	}

	sort(b, b + n);
	reverse(b, b + n);
	sort(a, a + n);
	memset(it, -1, sizeof(it));


	for (int i = 0; i < n; ++i) bid[b[i].second] = i;
	for (int i = 0; i < n; ++i) {
		long long got = a[i].first * (n - i);
		long long x = 0;
		for (int j = 0; j < K; ++j) {
			if (g[j].size()) {
				int id = rb[j][it[j]].second;
				if (id != -1) {
					long long now = got + g[j][id].first * x + g[j][id].second;

					if (now > res) {
						res = now;
					}
				}
				x += g[j].size();
			}
		}

		if (got > res) {
			res = got;
		}

		int id = bid[a[i].second];
		int bucket = id / K;
		int cnt = 0;
		active[id] = 1;

		rb[bucket].clear();
		g[bucket].clear();

		for (int j = bucket * K; j < (bucket + 1) * K; ++j) {
			if (j >= n) break;
			if (active[j]) {
				g[bucket].push_back({ b[j].first, (long long)b[j].first * (long long)(++cnt) });
			}
		}

		vector<pair<long long, long long> > st;
		sort(g[bucket].begin(), g[bucket].end());
		rb[bucket].push_back({ -INF, 0 });
		st.push_back(g[bucket][0]);
		it[bucket] = 0;

		for (int j = 1; j < g[bucket].size(); ++j) {
			while (st.size() && (st.back().first == g[bucket][j].first || intersect(st.back(), g[bucket][j]) + 1e-6 < rb[bucket].back().first)) {
				st.pop_back();
				rb[bucket].pop_back();
			}
			if (st.size()) {
				rb[bucket].push_back({ intersect(st.back(), g[bucket][j]), j });
			}
			else {
				rb[bucket].push_back({ -INF, j });
			}
			st.push_back(g[bucket][j]);
		}

		x = 0;

		for (int j = 0; j < K; ++j) {
			if (g[j].size()) {
				while (it[j] != rb[j].size() - 1 && rb[j][it[j] + 1].first <= x) {
					++it[j];
				}
				x += g[j].size();
			}
		}
	}

	cout << res << endl;
	return 0;
}

/*
50
36 28
50 29
10 10
47 1
50 47
33 6
33 15
36 14
37 7
22 15
32 27
41 24
33 18
42 30
42 40
8 1
14 1
33 13
48 43
40 39
31 2
26 10
9 4
39 31
23 17
35 6
20 1
41 23
47 9
17 8
38 25
33 5
35 31
27 9
31 13
49 49
27 4
42 17
22 1
15 15
42 7
20 10
40 28
35 28
11 10
47 6
28 11
47 17
18 6
39 36

*/