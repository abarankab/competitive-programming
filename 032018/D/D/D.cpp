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

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int res;
int n, mod;
vector<int> all;

void gen(int rest, int last = 1, int all = 0)
{
	if (rest == 0)
	{
		res += (all * all * all);
		return;
	}
	for (int i = last; i <= rest; ++i)
	{
		gen(rest - i, i, all + 1);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> n >> mod;
	for (int i = 1; i <= n; ++i)
	{
		gen(i);
		cout << res % mod << "\n";
		res = 0;
	}
	return 0;
}

