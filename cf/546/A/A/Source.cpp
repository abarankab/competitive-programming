#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100500, K = 300;

int n, q;
int a[MAXN], b[MAXN], t[MAXN * 4], need[MAXN * 4], last[MAXN];

void push(int v, int l, int r) {
	if (need[v]) {
		t[v] += need[v] * (r - l);
		if (r - l != 1) {
			need[v * 2] = need[v];
			need[v * 2 + 1] = need[v * 2 + 1];
		}
		need[v] = 0;
	}
}

void update(int v, int l, int r, int i, int x) {
	if (r - l == 1) {
		t[v] = x;
		return;
	}

	int m = (l + r) / 2;
	if (i < m) update(v * 2, l, m, i, x);
	else update(v * 2 + 1, m, r, i, x);
	t[v] = t[v * 2] + t[v * 2 + 1];
}

void update_seg(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);

	if (tl >= r || l >= tr) return;
	if (tl >= l && tr <= r) {
		need[v] = x;
	}

	int m = (tl + tr) / 2;
	update_seg(v * 2, tl, m, l, r, x);
	update_seg(v * 2 + 1, m, tr, l, r, x);
}

int get(int v, int tl, int tr, int l, int r) {
	push(v, tl, tr);

	if (tl >= r || l >= tr) return 0;
	if (tl >= l && tr <= r) return t[v];

	int m = (tl + tr) / 2;
	return get(v * 2, tl, m, l, r) + get(v * 2 + 1, m, tr, l, r);
}

int p[MAXN], sz[MAXN], rb[MAXN];

int root(int v) {
	if (p[v] == v) return v;
	p[v] = root(p[v]);
	return p[v];
}

void union_set(int a, int b) {
	if (sz[a] < sz[b]) {
		swap(a, b);
	}
	p[b] = a;
	sz[a] += sz[b];
	rb[a] = max(rb[a], rb[b]);
}

signed main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		p[i] = i;
		rb[i] = -1;
		sz[i] = 1;
	}
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < n - 1; ++i) {
		cin >> b[i];
	}
	cin >> q;
	for (int i = 0; i < q; ++i) {
		char tp;
		cin >> tp;
		if (tp == '+') {
			int id, x;
			cin >> id >> x;
			if (rb[root(id)] != -1) {
				update_seg(1, 1, n + 1, id, rb[root(id)] + 1, x);
				id = rb[root(id)] + 1;
			}
			while (id <= n && get(1, 1, n + 1, id, id + 1) < get(1, 1, n + 1, id - 1, id)) {
				rb[id]
			}
		}
	}
	return 0;
}