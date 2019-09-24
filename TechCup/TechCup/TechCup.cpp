// TechCup.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <queue>
#include <cstring>

typedef long double ld;

using namespace std;

const int N = 2 * 1e5;
const int AL = 26;

vector<string> arr;
int n;

bool flag = 0;

int main()
{
	cout.precision(30);
	ios_base::sync_with_stdio(0);

	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		arr.push_back(s);

		int used2[AL];
		memset(used2, 0, sizeof(used2));
		for (char ch : s)
		{
			used2[ch - 'a'] += 1;
		}

		for (int j = 0; j < AL; ++j)
		{
			if (used2[j] > 1 && !flag)
			{
				flag = 1;
			}
		}
	}

	if (flag)
	{
		cout << "NO\n";
		return 0;
	}

	for (int let = AL - 1; let >= 0; --let)
	{
		if (arr.size() == 1)
		{
			break;
		}
		char cur = let + 'a';
		string resl, resr;
		vector<pair<int, int> > used;

		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 0; j < arr[i].size(); ++j)
			{
				if (arr[i][j] == cur)
				{
					used.push_back({ i, j });
				}
			}
		}

		if (used.size() == 0)
		{
			continue;
		}

		for (pair<int, int> occ : used)
		{
			for (int i = occ.second + 1; i < arr[occ.first].size(); ++i)
			{
				int pos = i - occ.second - 1;
				if (pos + 1 <= resr.size() && resr[pos] != arr[occ.first][i])
				{
					cout << "NO" << endl;
					return 0;
				}
				else if (pos + 1 > resr.size())
				{
					resr += arr[occ.first][i];
				}
			}

			for (int i = occ.second - 1; i >= 0; --i)
			{
				int poslast = occ.second - i - 1;
				if ((int)resl.size() - 1 >= poslast && resl[resl.size() - poslast - 1] != arr[occ.first][i])
				{
					cout << "NO" << endl;
					return 0;
				}
				else if ((int)resl.size() - 1 < poslast)
				{
					resl = arr[occ.first][i] + resl;
				}
			}
		}

		bool f = 1;
		while (f)
		{
			int pos;
			f = 0;
			for (int i = 0; i < arr.size(); ++i)
			{
				for (int j = 0; j < arr[i].size(); ++j)
				{
					if (arr[i][j] == cur)
					{
						f = 1;
						pos = i;
					}
				}
			}

			if (f)
			{
				arr.erase(arr.begin() + pos);
			}
		}

		arr.push_back(resl + cur + resr);
	}

	sort(arr.begin(), arr.end());

	for (int i = 0; i < arr.size(); ++i)
	{
		cout << arr[i];
	}

	cout << endl;

	return 0;
}