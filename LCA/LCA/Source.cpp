#include <iostream>
#include <vector>

#define int long long

using namespace std;

const int N = (int)1e5 + 7;
const int EXP = 20;

int n, m, q[N], x, y, z;
vector<int> g[N];
int p[N][EXP];
int tin[N], tout[N], cnt;

void dfs(int v, int pr = 0)
{
	p[v][0] = pr;
	tin[v] = cnt++;

	for (int i = 1; i < EXP; ++i)
	{
		p[v][i] = p[p[v][i - 1]][i - 1];
	}

	for (int u : g[v])
	{
		if (u != pr)
		{
			dfs(u, v);
		}
	}

	tout[v] = cnt++;
}


bool parent(int to, int son)
{
	return (tin[son] < tout[to] && tin[son] > tin[to]);
}


int lca(int u, int v)
{
	if (parent(u, v))
	{
		return u;
	}
	else if (parent(v, u))
	{
		return v;
	}

	for (int i = EXP - 1; i >= 0; --i)
	{
		if (!parent(p[u][i], v))
		{
			u = p[u][i];
		}
	}

	return p[u][0];
}


signed main()
{
	cin >> n >> m;
	for (int i = 0; i < n - 1; ++i)
	{
		int u;
		cin >> u;
		g[u].push_back(i + 1);
		g[i + 1].push_back(u);
	}
	dfs(0);
	cin >> q[0] >> q[1] >> x >> y >> z;
	int res = 0;
	for (int i = 2; i < 2 * m; ++i)
	{
		q[i] = (x * q[i - 2] + y * q[i - 1] + z) % n;
	}
	int u = q[0], v = q[1];
	res += lca(u, v);
	for (int i = 1; i < m; ++i)
	{
		res += lca(u, v);
		u = (lca(u, v) + q[2 * (i + 1) - 2]) % n;
		v = q[2 * (i + 1) - 1];
	}
	cout << res << endl;
}