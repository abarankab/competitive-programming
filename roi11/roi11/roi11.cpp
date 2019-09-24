#include <algorithm>
#include <cassert>
#include <fstream>
#include <utility>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <set>
#include <map>

#define f first
#define s second

#pragma warning(disable:4996)

using namespace std;

template<class T> inline void chkmin(T &a, T b) {
	if (a > b) a = b;
}

template<class T> inline void chkmax(T &a, T b) {
	if (a < b) a = b;
}

typedef long long ll;
typedef long double ld;

#include <iostream>
//const string FILENAME = "test";
//ifstream cin(FILENAME + ".in");
//ofstream cout(FILENAME + ".out");

const int MAXN = 3e5 + 7;
const int INF = 1e9;

int sz[3];
int ppl[3][MAXN];
int ans[3];
int a, b, c, n;
int csz[3];
int cans[3];
int res;

void Solve2(int c1) {
	int m1 = a + b + c - c1;
	int l = -1, r = csz[0];
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (m + 2 <= m1 && m1 - m - 2 < csz[1] && ppl[0][m] < ppl[1][m1 - m - 2])
			l = m;
		else
			r = m;
	}
	if (l == -1) return;
	int cres = abs(l - a - 1) + abs(m1 - l + 1 - b);
	if (res > cres) {
		res = cres;
		ans[0] = l - 1;
		ans[1] = m1 - l + 1;
		ans[2] = c1;
	}
	if (0 <= m1 - 2 && m1 - 2 < csz[1] && ppl[0][0] < ppl[1][m1 - 2])
		cres = abs(a - 1) + abs(b - m1 + 1);
	if (res > cres) {
		res = cres;
		ans[0] = 1;
		ans[1] = m1 - 1;
		ans[2] = c1;
	}
	if (0 <= m1 - csz[0] - 1 && m1 - csz[0] - 1 < csz[1] && ppl[0][csz[0] - 1] < ppl[1][m1 - csz[0] - 1])
		cres = abs(csz[0] - a) + abs(m1 - csz[0] - b);
	if (res > cres) {
		res = cres;
		ans[0] = csz[0];
		ans[1] = m1 - csz[0];
		ans[2] = c1;
	}
	if (0 <= m1 - csz[1] - 1 && m1 - csz[1] - 1 < csz[0] && ppl[0][m1 - csz[1] - 1] < ppl[1][csz[1] - 1])
		chkmin(cres, abs(m1 - csz[1] - a) + abs(csz[1] - b));
	if (res > cres) {
		res = cres;
		ans[0] = m1 - csz[1];
		ans[1] = csz[1];
		ans[2] = c1;
	}
	if (0 <= m1 - 2 && m1 - 2 < csz[0] && ppl[0][m1 - 2] < ppl[1][0])
		chkmin(cres, abs(1 - a) + abs(m1 - 1 - b));
	if (res > cres) {
		res = cres;
		ans[0] = m1 - 1;
		ans[1] = 1;
		ans[2] = c1;
	}
}

void Solve() {
	mt177
	cin >> a >> b >> c >> n;
	sz[0] = sz[1] = sz[2] = 0;
	for (int i = 0; i < n; ++i) {
		int q, w;
		cin >> q >> w;
		q -= 1994;
		ppl[q][sz[q]] = -w;
		++sz[q];
	}
	for (int q = 0; q < 3; ++q)
		sort(ppl[q], ppl[q] + sz[q]);
	res = INF;
	csz[0] = csz[1] = 0;
	for (int i = 0; i < sz[2]; ++i) {
		while (ppl[0][csz[0]] < ppl[2][i]) ++csz[0];
		while (ppl[1][csz[1]] < ppl[2][i]) ++csz[1];
		Solve2(i + 1);
	}
}

int main() {
	int k;
	cin >> k;
	for (int q = 0; q < k; ++q) {
		Solve();
		if (res >= INF)
			cout << "-1\n";
		else
			cout << res << ' ' << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n';
	}
}