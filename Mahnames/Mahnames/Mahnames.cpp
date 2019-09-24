// Mahnames.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> occur_a[26], occur_b[26];
string a, b, res;
int ai = -1, bi = -1;
int l, r;

int main()
{
	cin >> a >> b;
	for (int i = 0; i < a.size(); ++i)
	{
		occur_a[a[i] - 'a'].push_back(i);
	}
	for (int i = 0; i < b.size(); ++i)
	{
		occur_b[b[i] - 'a'].push_back(i);
	}
	for (int i = 25; i >= 0; --i)
	{
		l = r = 0;
		while (l < occur_a[i].size() && r < occur_b[i].size())
		{
			if (occur_a[i][l] < ai)
			{
				++l;
				continue;
			}
			if (occur_b[i][r] < bi)
			{
				++r;
				continue;
			}
			res += 'a' + i;
			ai = max(occur_a[i][l], ai);
			bi = max(occur_b[i][r], bi);
			++l;
			++r;
		}
	}
	cout << res;
    return 0;
}

