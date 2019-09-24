// 14022018.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

int g, d, f;
vector<int> goal;
vector<int> defence;
vector<int> offence;
vector<int> all;

signed main()
{
	cin >> g >> d >> f;
	goal.resize(g);
	defence.resize(d);
	offence.resize(f);
	for (int i = 0; i < g; ++i)
	{
		cin >> goal[i];
		all.push_back(goal[i]);
	}
	for (int i = 0; i < d; ++i)
	{
		cin >> defence[i];
		all.push_back(defence[i]);
	}
	for (int i = 0; i < f; ++i)
	{
		cin >> offence[i];
		all.push_back(offence[i]);
	}

	sort(goal.begin(), goal.end());
	sort(defence.begin(), defence.end());
	sort(offence.begin(), offence.end());
	sort(all.begin(), all.end());

	int res = 0;

	int max_num = all[all.size() - 1] + 100;

	for (int min_num : all)
	{
		int type = -1;
		int lg = max_num, hg = -1; //low bound & high bound
		bool flag = 0;
		for (int i = 0; i < g; ++i)
		{
			if (goal[i] == min_num)
			{
				type = 0;
			}
			if (!flag && goal[i] >= min_num)
			{
				flag = 1;
				lg = i;
			}
			if (flag && goal[i] <= 2 * min_num)
			{
				hg = i;
			}
		}

		int ld = max_num, hd = -1; //low bound & high bound
		flag = 0;
		for (int i = 0; i < d; ++i)
		{
			if (defence[i] == min_num)
			{
				type = 1;
			}
			if (!flag && defence[i] >= min_num)
			{
				flag = 1;
				ld = i;
			}
			if (flag && defence[i] <= 2 * min_num)
			{
				hd = i;
			}
		}

		int lo = max_num, ho = -1; //low bound & high bound
		flag = 0;
		for (int i = 0; i < f; ++i)
		{
			if (offence[i] == min_num)
			{
				type = 2;
			}
			if (!flag && offence[i] >= min_num)
			{
				flag = 1;
				lo = i;
			}
			if (flag && offence[i] <= 2 * min_num)
			{
				ho = i;
			}
		}

		int can_goal = hg - lg + 1;
		int can_defence = hd - ld + 1;
		int can_offence = ho - lo + 1;

		int goal_permutations = can_goal;
		int defence_permutations = can_defence * (can_defence - 1);
		int offence_permutations = can_offence * (can_offence - 1) * (can_offence - 2);

		if (can_goal >= 1 && can_defence >= 2 && can_offence >= 3)
		{
			if (type == 0)
			{
				goal_permutations = 1;
				res += goal_permutations * defence_permutations * offence_permutations / 12;
			}
			else if (type == 1)
			{
				defence_permutations = can_defence - 1;
				res += goal_permutations * defence_permutations * offence_permutations / 6;
			}
			else
			{
				offence_permutations = (can_offence - 1) * (can_offence - 2);
				res += goal_permutations * defence_permutations * offence_permutations / 4;
			}
		}
	}

	cout << res;

    return 0;
}