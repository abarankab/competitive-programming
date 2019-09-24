#include <iostream>
#include <string>
#include <vector>
using namespace std;
char inv(char c)
{
	return (c == '-' ? '+' : '-');
}

int main()
{
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		string a, b;
		cin >> a >> b;
		a.push_back(0);
		b.push_back(0);
		vector<int> cnt(1, 1);
		char last = a.front();
		bool pos = true;
		vector<int> otl;
		for (int i = 1; i < a.size() && pos; ++i) {
			if (a[i] == a[i - 1]) {
				++cnt.back();
				if (b[i] != b[i - 1])
					pos = false;
			}
			else {
				if (b[i - 1] != a[i - 1]) {
					if (cnt.size() > 1 && cnt[cnt.size() - 2] > cnt.back()) {
						cnt[cnt.size() - 2] += cnt.back();
						cnt.pop_back();
						last = inv(last);
					}
					else
						otl.push_back(cnt.size() - 1);
				}
				while (cnt.size() > 1 && otl.size() && otl.back() == cnt.size() - 2 && cnt.back() > cnt[cnt.size() - 2]) {
					if (cnt.size() == 2) {
						cnt.front() += cnt.back();
						cnt.pop_back();
					}
					else {
						cnt[cnt.size() - 3] += cnt[cnt.size() - 2] + cnt.back();
						cnt.pop_back();
						cnt.pop_back();
					}
					otl.pop_back();
				}
				if (last == a[i])
					++cnt.back();
				else {
					last = inv(last);
					cnt.push_back(1);
				}
			}
		}
		if (pos && otl.empty())
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}
