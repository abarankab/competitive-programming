#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector <int> x(n), y(n);
	int maxY = 0;
	int minY = (int)1e9;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		if (y[i] > maxY) {
			maxY = y[i];
		}
		if (y[i] < minY) {
			minY = y[i];
		}
	}
	vector <int> minX(maxY, -1);
	vector <int> maxX(maxY, -1);
	for (int i = 0; i < n; i++) {
		int ii = (i + 1) % n;
		if (x[i] == x[ii]) {
			if (y[i] < y[ii]) {
				for (int yy = y[i]; yy < y[ii]; yy++) {
					maxX[yy] = x[i];
				}
			}
			else {
				for (int yy = y[ii]; yy < y[i]; yy++) {
					minX[yy] = x[i];
				}
			}
		}
	}
	int ans = (int)1e9;
	for (int sk = 0; sk < k; sk++) {
		int cur = 0;
		for (int y = minY; y < maxY; y++) {
			assert(minX[y] != -1);
			assert(minX[y] <= maxX[y]);
			int x = (y + sk) % k;
			while (x <= minX[y]) {
				x += k;
			}
			cur++;
			while (x < maxX[y]) {
				x += k;
				cur++;
			}
		}
		if (cur < ans) {
			ans = cur;
		}
	}
	cout << ans;
	return 0;
}
