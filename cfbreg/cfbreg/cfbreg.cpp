// cfbreg.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

typedef long double ld;

bool cmp(pair<int, int> a, pair<int, int> b)
{
	return a.first * b.second < b.first * a.second;
}

vector<pair<int, int> > arr;

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		int a, b;
		cin >> a >> b;
		arr.push_back({ a, b });
	}
	sort(arr.begin(), arr.end(), cmp);
	cout.precision(20);
	cout << (ld)arr[0].first * (ld)m / (ld)arr[0].second << endl;
	return 0;
}

