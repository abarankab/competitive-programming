// Jedi.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> a;

void mod(int pos, int deg)
{
	a[pos] &= (1 << deg);
}

int main()
{
	int n;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int tmp;
			cin >> tmp;
			if (i != j)
			{
				int deg = 0;
				while (tmp != 0)
				{
					if (tmp & 1)
					{
						mod(i, deg);
						mod(j, deg);
					}
					tmp >> 1;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
    return 0;
}

