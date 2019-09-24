#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

#pragma comment(linker, "/STACK:256000000")
typedef long long ll;

const int MAXN = 105, MAXA = 2e6 + 5;

int n, a;
int l[MAXN], r[MAXN], c[MAXN];
ll dp[MAXA];
deque<int> mn[MAXN];

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n >> a;
	for (int i = 0; i < n; ++i) cin >> l[i] >> r[i] >> c[i];
	for (int x = a; x >= 0; --x) {
		ll now = 1e9 * (ll)x;
		for (int move = 0; move < n; ++move) {
			if (r[move] + x == a) {
				for (int i = r[move] + x; i >= l[move] + x; --i) {
					while (mn[move].size() && dp[mn[move].front()] > dp[i]) {
						mn[move].pop_front();
					}
					mn[move].push_front(i);
				}
			}

			if (r[move] + x <= a) {
				now = max(now, dp[mn[move].back()] - c[move]);

				while (mn[move].size() && mn[move].back() >= x + r[move]) {
					mn[move].pop_back();
				}

				while (mn[move].size() && dp[mn[move].front()] > dp[x + l[move] - 1]) {
					mn[move].pop_front();
				}

				mn[move].push_front(x + l[move] - 1);
			}
		}
		dp[x] = now;
	}
	cout << dp[0] << "\n";
	return 0;
}