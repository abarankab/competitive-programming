// B.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

string s;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	string tmp;
	int all = 0;
	while (in >> tmp)
	{
		s += tmp + '_';
		all += tmp.size();
	}

	set<vector<int> > st;
	string dup = s + s;
	int res = 1;
	for (int i = 0; i < s.size(); ++i)
	{
		int last = 0;
		int sum = 0;
		for (int j = i; j - i + 1 < s.size(); ++j)
		{
			if (dup[j] == '_')
			{
				sum += last;
				last = 0;
			}
			else
			{
				last <<= 1;
				last += dup[j] == '1';
			}

			if (dup[i] != '_' && dup[j + 1] != '_')
			{
				vector<int> border;
				border.push_back(j % s.size());
				
				int left = s.size() - (j - i + 1);
				string to = dup.substr(j + 1, left);

				int need = last + sum;
				int lst = 0, sm = 0;
				bool flag = 1;

				for (int k = 0; k < to.size(); ++k)
				{
					char x = to[k];
					if (x == '_')
					{
						sm += lst;
						lst = 0;
					}
					else
					{
						flag = 0;
						lst <<= 1;
						lst += x == '1';
					}

					if (lst + sm == need)
					{
						flag = 1;
						sm = 0;
						lst = 0;

						if (dup[k + j + 2] == '_')
						{
							border.push_back((j + k + 2) % s.size());
						}
						else
						{
							border.push_back((j + k + 1) % s.size());
						}
					}
					else if (lst + sm > need)
					{
						continue;
					}
				}

				sort(border.begin(), border.end());

				if (flag)
				{
					st.insert(border);
				}
			}
		}
	}

	cout << st.size() + all << endl;
	    return 0;
}

