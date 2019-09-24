// region_d5_A.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;

	vector<pair<int, char> > cnt;
	vector<int> count(26);

	for (int i = 0; i < n; ++i)
	{
		++count[s[i] - 'a'];
	}

	for (int i = 0; i < 26; ++i)
	{
		cnt.push_back({ count[i], 'a' + i });
	}
	vector<queue<char> > change(26);
	for (int asd = 0; asd < k; ++asd)
	{
		int mxr = -1;
		int initial = -1;
		for (int i = 0; i < 26; ++i)
		{
			for (int j = 0; j < 26; ++j)
			{
				if (cnt[i].first != 0 && cnt[j].first != 0)
				{
					mxr = max(abs(cnt[i].first - cnt[j].first), mxr);
				}
			}
		}
		initial = mxr;
		pair<char, char> res_now;
		for (char from = 'a'; from <= 'z'; ++from)
		{
			for (char to = 'a'; to <= 'z'; ++to)
			{
				if (from != to && cnt[from - 'a'].first != 0)
				{
					cnt[from - 'a'].first--;
					cnt[to - 'a'].first++;
					int cur_res = -1;
					for (int i = 0; i < 26; ++i)
					{
						for (int j = 0; j < 26; ++j)
						{
							if (cnt[i].first != 0 && cnt[j].first != 0)
							{
								cur_res = max(abs(cnt[i].first - cnt[j].first), cur_res);
							}
						}
					}
					if (cur_res < mxr)
					{
						res_now = { from, to };
						mxr = cur_res;
					}
					cnt[from - 'a'].first++;
					cnt[to - 'a'].first--;
				}
			}
		}
		if (mxr == initial)
		{
			break;
		}
		change[res_now.first - 'a'].push(res_now.second);
		cnt[res_now.first - 'a'].first--;
		cnt[res_now.second - 'a'].first++;
		if (mxr == 0)
		{
			break;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (!change[s[i] - 'a'].empty())
		{
			cout << change[s[i] - 'a'].front();
			change[s[i] - 'a'].pop();
		}
		else
		{
			cout << s[i];
		}
	}
    return 0;
}

