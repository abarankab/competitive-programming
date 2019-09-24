// region_d4_C.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int n;
	vector<int> arr;
	vector<pair<int, int> > stable;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	int l = 0, r = 0;
	set<int> done;
	while (r < n - 1)
	{
		int to;
		if (done.size() != 0)
		{
			auto tmp = prev(done.lower_bound(arr[l]));
			if (tmp != done.end())
			{
				to = *tmp;
			}
		}
		while (r < n - 1 && arr[r + 1] > arr[r] && (done.size() == 0 || (prev(done.lower_bound(arr[r])) == done.end() || to == *prev(done.lower_bound(arr[r + 1])))))
		{
			++r;
		}
		done.insert(arr[l]);
		l = r + 1;
		++r;
	}
	cout << done.size() << endl;
    return 0;
}

