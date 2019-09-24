#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 3e5 + 5;

int n, l, r, res;
int mn[MAXN], mx[MAXN], a[MAXN];

vector<int> s;

signed main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = n - 1; i >= 0; --i) {
		while (!s.empty() && a[s.back()] < a[i]) {
			s.pop_back();
		}
		if (s.empty()) mx[i] = MAXN;
		else mx[i] = s.back();
		s.push_back(i);
	}
	s.clear();
	for (int i = n - 1; i >= 0; --i) {
		while (!s.empty() && a[s.back()] > a[i]) {
			s.pop_back();
		}
		if (s.empty()) mn[i] = MAXN;
		else mn[i] = s.back();
		s.push_back(i);
	}
	s.clear();
	while (l < n) {
		r = l;
		int rb = mn[l];
		while (rb != MAXN && a[rb] == a[l]) rb = mn[rb];
		while (mx[r] != MAXN && mx[r] < rb) {
			r = mx[r];
		}
		++res;
		l = r + 1;
	}
	cout << res << endl;
	return 0;
}