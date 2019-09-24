
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int n, m;

struct inc
{
	int x;
	bool nul;

	inc()
	{
		x = 0;
		nul = false;
	}

	inc(int to)
	{
		if (to)
		{
			x = to;
			nul = 0;
		}
		else
		{
			x = 0;
			nul = 1;
		}
	}

	void operator+=(inc b)
	{
		if (b.nul)
		{
			x = 0;
			nul = 1;
		}
		x += b.x;
	}
};

struct node
{
	int val;
	bool need;
	inc to;

	node()
	{
		val = 0;
		need = false;
		to = inc();
	}
};

vector<node> t;

void push(int v, int lb, int rb)
{
	if (t[v].need)
	{
		if (rb - lb == 1)
		{
			if (t[v].to.nul)
			{
				t[v].val = 0;
			}
			t[v].val = t[v].val = t[v].to.x;
		}
		else
		{
			t[v * 2].to += t[v].to;
			t[v * 2 + 1].to += t[v].to;
			t[v].need = 0;
			t[v].to = inc();
			t[v * 2].need = 1;
			t[v * 2 + 1].need = 1;
		}
	}
}

void add(int l, int r, int lb, int rb, int to, int v = 1)
{
	push(v, lb, rb);
	if (l >= r || l >= rb || r <= lb)
	{
		return;
	}
	if (l <= lb && r >= rb)
	{
		t[v].to += inc(to);
		t[v].need = 1;
		return;
	}
	add(l, r, lb, (lb + rb) / 2, to, 2 * v);
	add(l, r, (lb + rb) / 2, rb, to, 2 * v + 1);
}

int get(int i, int lb, int rb, int v = 1)
{
	push(v, lb, rb);
	if (rb - lb == 1)
	{
		return t[v].val;
	}
	if (i < (lb + rb) / 2)
	{
		return get(i, lb, (lb + rb) / 2, 2 * v);
	}
	else
	{
		return get(i, (lb + rb) / 2, rb, 2 * v + 1);
	}
}

set<int> st;
map<int, int> convert;
vector<pair<int, int> > q;
vector<int> need;
int cnt = 0;

int main()
{
	cin >> n >> m;
	st.insert(0);
	st.insert(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int l, r, g;
		cin >> l >> r >> g;
		st.insert(l);
		st.insert(r);
		st.insert(g);
		q.push_back({ l, r });
		need.push_back(g);
	}
	while (!st.empty())
	{
		int now = *st.begin();
		convert[now] = ++cnt;
		st.erase(now);
	}
	t.resize(4 * cnt);
	for (int i = 0; i < m; ++i)
	{
		q[i].first = convert[q[i].first];
		q[i].second = convert[q[i].second];
		need[i] = convert[need[i]];
	}
	for (int i = 0; i < m; ++i)
	{
		add(1, q[i].first, 1, cnt + 1, 0);
		add(q[i].first, q[i].second + 1, 1, cnt + 1, 1);
		add(q[i].second + 1, convert[n + 1], 1, cnt + 1, 0);
		cout << get(need[i], 1, cnt + 1) << endl;
	}
	return 0;
}

