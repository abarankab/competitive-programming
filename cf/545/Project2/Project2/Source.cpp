#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5, MAXK = 5005;
const int A = 18;

struct st {
	int first, second;

	st(int a, int b) {
		first = a, second = b; 
	}

	st() {}
};

st table[2 * MAXN][A]; 
int h[MAXN], tin[MAXN], close[2 * MAXN];
int n, k, cnt;
int pw[2 * A];
vector<int> g[MAXN];
st order[2 * MAXN];
int path[MAXK][3];
int res = -1, x, y;

st mx(st a, st b) {
	if ((a.first == b.first && a.second > b.second) || a.first > b.first) return a;
	return b;
}

st mn(st a, st b) {
	if ((a.first == b.first && a.second < b.second) || a.first < b.first) return a;
	return b;
}

int mx(int a, int b) {
	if (a > b) return a;
	return b;
}

int mn(int a, int b) {
	if (a < b) return a;
	return b;
}

void dfs(int v = 0, int p = 0) {
	h[v] = h[p] + 1;
	order[cnt] = st(h[v], v);
	tin[v] = cnt++;
	for (int u : g[v]) {
		dfs(u, v);
		order[cnt++] = st(h[v], v);
	}
}

int get(int u, int v) {
	if (tin[u] > tin[v]) swap(u, v);
	
	int l = tin[u], r = tin[v];
	int k = close[r - l + 1];
	return mn(table[l][k], table[r - pw[k] + 1][k]).second;
}

int inter(int a, int b, int c, int d) {
	int bottom = get(a, c);
	return mx(0, h[bottom] - mx(h[b], h[d]));
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	close[1] = 0;
	h[0] = -1;
	pw[0] = 1;
	for (int i = 1; i < 2 * A; ++i) {
		pw[i] = pw[i - 1] * 2;
	}
	for (int i = 2; i < 2 * MAXN; ++i) {
		close[i] = close[i - 1];
		if (pw[close[i] + 1] <= i) ++close[i];
	}
	cin >> n >> k;
	for (int i = 0; i < n - 1; ++i) {
		int p;
		cin >> p;
		g[p - 1].push_back(i + 1);
	}
	dfs(0);
	for (int i = 0; i < 2 * n - 1; ++i) table[i][0] = order[i];
	for (int k = 1; k < A; ++k) {
		for (int i = 0; i + pw[k] - 1 < 2 * n - 1; ++i) {
			table[i][k] = mn(table[i][k - 1], table[i + pw[k - 1]][k - 1]);
		}
	}
	for (int i = 0; i < k; ++i) {
		cin >> path[i][0] >> path[i][1];
		--path[i][0];
		--path[i][1];
		path[i][2] = get(path[i][0], path[i][1]);
		for (int j = 0; j < i; ++j) {
			int s = path[i][0], f = path[i][1], m = path[i][2];
			int s1 = path[j][0], f1 = path[j][1], m1 = path[j][2];
			int now = inter(s, m, s1, m1) + inter(s, m, f1, m1) + inter(f, m, s1, m1) + inter(f, m, f1, m1);
			if (now > res) {
				res = now;
				x = j + 1, y = i + 1;
			}
		}
	}
	cout << res << "\n";
	cout << x << " " << y << "\n";
	return 0;
}
