// Course_main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

const int N = (int) 1e5 + 5;
int n, k;

vector<int> v[N];
unordered_map<pair<int, int >, int> idtonum;
int mark[N];
int now = 0;


int get_lca(int a, int b)
{
	//TODO
}


void count(int u)
{
	now += mark[u];
	for (int i = 0; i < v[u].size(); ++i)
	{
		idtonum[{u, v[u][i]}] = now;
		count(v[u][i]);
	}
}


int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
	}
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		int a, b;
		cin >> a >> b;
		int lca = get_lca(a, b);
		if (a == lca)
		{
			mark[a] = 1;
			mark[b] = -1;
		}
		else if (b == lca)
		{
			mark[b] = 1;
			mark[a] = -1;
		}
		else
		{
			mark[a] = -1;
			mark[b] = -1;
			mark[lca] = 1;
		}
	}
	count(0);
    return 0;
}

