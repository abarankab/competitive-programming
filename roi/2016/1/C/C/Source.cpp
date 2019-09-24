#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 5;

struct st {
	ll t[MAXN * 4];

	st() {}

	void update(int v, int l, int r, int i, int x) {
		if (r - l == 1) {
			t[v] += x;
			return;
		}

		int m = (l + r) / 2;
		if (i < m) update(v * 2, l, m, i, x);
		else update(v * 2 + 1, m, r, i, x);

		t[v] = t[v * 2] + t[v * 2 + 1];
	}

	ll get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || l >= tr) return 0;
		else if (tr <= r && tl >= l) return t[v];

		int m = (tl + tr) / 2;
		return get(v * 2, tl, m, l, r) + get(v * 2 + 1, m, tr, l, r);
	}

	int get_l(int v, int l, int r, ll need) {
		if (r - l == 1) return l;

		int m = (l + r) / 2;
		if (t[v * 2 + 1] < need) return get_l(v * 2, l, m, need - t[v * 2 + 1]);
		else return get_l(v * 2 + 1, m, r, need);
	}
};

st s1, s2;
ll res, need, cost, all;
int n, m, p, sz, last;
int x[MAXN], y[MAXN];
int a[MAXN], b[MAXN], c[MAXN], id[MAXN];
pair<int, int> cs[MAXN];
tuple<int, bool, int> event[2 * MAXN];

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n >> m >> p;
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> a[i];
		event[i] = { x[i], 0, i };
	}
	for (int i = 0; i < m; ++i) {
		cin >> y[i] >> b[i] >> c[i];
		event[n + i] = { y[i], 1, i };
		cs[i] = { c[i], i };
	}
	sort(event, event + n + m);
	sort(cs, cs + m);
	sz = unique(cs, cs + m) - cs;
	for (int i = 0; i < sz; ++i) {
		id[cs[i].second] = i;
	}
	for (int i = 0; i < n + m; ++i) {
		int x = get<0>(event[i]);
		int move = x - last;
		last = x;

		bool type = get<1>(event[i]);
		int now = get<2>(event[i]);

		cost += (ll)move * (ll)p;

		if (type) { // sell
			s1.update(1, 1, sz + 1, id[now] + 1, b[now]);
			s2.update(1, 1, sz + 1, id[now] + 1, (ll)b[now] * (ll)c[now]);
		}
		else {
			all += a[now];
		}
		
		int l = s1.get_l(1, 1, sz + 1, all);
		ll got = s2.get(1, 1, sz + 1, l + 1, sz + 1) + min(s1.get(1, 1, sz + 1, l, l + 1), (all - s1.get(1, 1, sz + 1, l + 1, sz + 1))) * (ll)cs[l - 1].first;
		if (got - cost > res) {
			res = got - cost;
		}
	}
	cout << res << endl;
	return 0;
}