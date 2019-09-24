/*
▄███████▀▀▀▀▀▀███████▄
░▐████▀▒ЗАПУСКАЕМ▒▀██████▄
░███▀▒▒▒▒▒ДЯДЮ▒▒▒▒▒▒▀█████
░▐██▒▒▒▒▒▒БОГДАНА▒▒▒▒▒████▌
░▐█▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▌
░░█▒▄▀▀▀▀▀▄▒▒▄▀▀▀▀▀▄▒▐███▌
░░░▐░░░▄▄░░▌▐░░░▄▄░░▌▐███▌
░▄▀▌░░░▀▀░░▌▐░░░▀▀░░▌▒▀▒█▌
░▌▒▀▄░░░░▄▀▒▒▀▄░░░▄▀▒▒▄▀▒▌
░▀▄▐▒▀▀▀▀▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒█
░░░▀▌▒▄██▄▄▄▄████▄▒▒▒▒█▀
░░░░▄██████████████▒▒▐▌
░░░▀███▀▀████▀█████▀▒▌
░░░░░▌▒▒▒▄▒▒▒▄▒▒▒▒▒▒▐
░░░░░▌▒▒▒▒▀▀▀▒▒▒▒▒▒▒▐

*/
#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <cmath>
#include <bitset>
#include <cassert>
#include <queue>
#include <stack>
#include <deque>
#include <cassert>
#include <iomanip>
#include <random>

using namespace std;

vector<pair<int, int> > arr;

string str;

bool correct(string s, int correct_black)
{
	char type = s[0];
	int cnt = 0;
	int black_cnt = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		black_cnt += (s[i] == '*');
	}
	for (int i = 1; i < s.size(); ++i)
	{
		if (s[i] != type)
		{
			++cnt;
			type = s[i];
		}
	}
	cnt += (int(s[0] == '*') + int(s[s.size() - 1] == '*'));
	return (cnt == 2) && (black_cnt == correct_black);
}

signed main() {
	//freopen("black.in", "r", stdin);
	//freopen("black.out", "w", stdout);

	int n, m, s, k;
	cin >> n >> m >> s >> k;
	cin >> str;
	if (!correct(str, s))
	{
		cout << "Impossible";
	}
	else
	{
		string result = ((s == 1 || m == s || k == 1 || k == m) ? "Unique" : "Ambiguous");
		cout << result;
	}
	return 0;
}