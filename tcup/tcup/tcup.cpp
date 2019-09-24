// tcup.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

//#define int long long

using namespace std;

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

const int MAXN = 3e5 + 5;
const int MAXA = 1.5e7 + 5;
int n, arr[MAXN], g, ans = -1;
bool used[MAXA];
int need[MAXA];

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		if (i) {
			g = gcd(arr[i], g);
		}
		else {
			g = arr[0];
		}
	}
	for (int i = 0; i < n; ++i) {
		arr[i] /= g;
		++need[arr[i]];
	}
	for (int i = 2; i < MAXA; ++i) {
		int cur = 0;
		if (!used[i]) {
			for (int q = i; q < MAXA; q += i) {
				cur += need[q];
				used[q] = 1;
			}
		}
		ans = max(ans, cur);
	}
	if (ans) cout << n - ans;
	else cout << -1;
    return 0;
}

