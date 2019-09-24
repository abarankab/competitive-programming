// qqqq.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>

using namespace std;

const int MAXN = 3005;

bool more[MAXN];
pair<int, int> ppl[MAXN];
int cnt[MAXN];
set<int> waow;

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int q, c;
		cin >> q >> c;
		++cnt[--q];
		if (q != 0) {
			ppl[i] = { q, c };
		}
	}
	for (int i = 1; i < m; ++i) {
		if (cnt[i] > cnt[0]) {
			more[i] = 1;
		}
	}
	for (pair<int, int> p: ppl) {
		if (more[p.first]) {

		}
	}
    return 0;
}

