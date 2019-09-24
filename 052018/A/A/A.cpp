// A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 250005, MAXC = 65540;

int n, s[MAXN];
vector<int> pos[MAXC];
vector<int> posr[MAXC];

int main()
{
	cin >> n;
	if (n % 2 == 1)
	{
		cout << "0\n";
		return 0;
	}

	for (int i = 0; i < n; ++i)
	{
		cin >> s[i];
		pos[s[i]].push_back(i);
		posr[s[i]].push_back(-i);
	}
	int minr = 2 * n;
	for (int i = 0; i < MAXC; ++i)
	{
		if (pos[i].size() != 0)
		{
			reverse(posr[i].begin(), posr[i].end());
			for (int j = 0; j < pos[i].size(); ++j)
			{
				int x = pos[i][j];
				int needed = (n - x - 1);
				auto p1 = lower_bound(pos[i].begin(), pos[i].end(), needed);
				auto p2 = lower_bound(posr[i].begin(), posr[i].end(), -needed);
				if (p1 != pos[i].end())
				{
					int ind = p1 - pos[i].begin();
					if (ind == j && j + 1 < pos[i].size())
					{
						++ind;
						minr = min(abs(needed - pos[i][ind]), minr);
					}
					else if (ind != j)
					{
						minr = min(abs(needed - pos[i][ind]), minr);
					}
				}
				if (p2 != posr[i].end())
				{
					int ind = (posr[i].size() - (p2 - posr[i].begin()) - 1);
					if (ind == j && j - 1 >= 0)
					{
						--ind;
						minr = min(abs(needed - pos[i][ind]), minr);
					}
					else if (ind != j)
					{
						minr = min(abs(needed - pos[i][ind]), minr);
					}
				}
			}
		}
	}
	cout << minr << endl;
    return 0;
}

