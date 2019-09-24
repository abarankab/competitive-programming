// kefiras.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> dp;
vector<pair<int, int> > fridge;
vector<pair<int, int> > shop;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		fridge.push_back({ tmp, i });
	}
	for (int i = 0; i < m; ++i)
	{
		int tmp;
		cin >> tmp;
		shop.push_back({ tmp, i });
	}
	sort(fridge.begin(), fridge.end());
	sort(shop.begin(), shop.end());
	int i = 0, j = 0, day = 0;

	vector<int> res;

	while (i < n)
	{
		if (fridge[i].first - day < 0)
		{
			cout << -1 << endl;
			return 0;
		}

		if (i == n - 1)
		{
			break;
		}

		while (shop[j].first - day < 0)
		{
			++j;
		}

		int jmod = 0;
		int next = min(i + k, n - 1);
		while (j + 1 < m && shop[j + 1] <= fridge[next - jmod - 1] && jmod <= k && next - jmod - 1 >= 0 && next - jmod - 1 < n && fridge[next - jmod - 1].first - day >= 0)
		{
			++jmod;
			++j;
			res.push_back(fridge[j].second + 1);
		}
		
		i = next - jmod;

		++day;
	}

	cout << res.size() << endl;
	for (int c = 0; c < res.size(); ++c)
	{
		cout << res[c] << " ";
	}
	cout << endl;

	return 0;
}