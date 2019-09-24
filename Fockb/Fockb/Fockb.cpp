// Dathday2.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>
#include <map>

#pragma warning(disable : 4996)

using namespace std;

const int MAXN = 1e6 + 228;

int n, root;
vector<int> bright;
vector<int> g[MAXN];
int need;
int par, tmp;
int root_sz;
int sz[MAXN];
int h[MAXN];
int cnt;
int last[MAXN];
bool has[MAXN];
vector<int> ok;

bool cmp(int a, int b)
{
	return h[a] < h[b];
}

int dfs(int v, int par = root)
{
	h[v] = v == par ? 0 : h[par] + 1;
	sz[v] = bright[v];
	for (int u : g[v])
	{
		sz[v] += dfs(u, v);
		has[v] |= has[u];
		last[v] = has[u] ? last[u] : last[v];
	}
	has[v] |= (sz[v] == need);
	last[v] = (sz[v] == need) ? v : last[v];
	return sz[v];
}

signed main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d", &par, &tmp);
		bright.push_back(tmp);
		root_sz += tmp;
		if (par != 0)
		{
			g[par - 1].push_back(i);
		}
		else
		{
			root = i;
		}
	}
	if (root_sz % 3 != 0)
	{
		printf("%s", "-1");
		return 0;
	}
	need = root_sz / 3;
	dfs(root);
	for (int v = 0; v < n; ++v)
	{
		int cnt = 0;
		int last_u = -1;

		for (int u : g[v])
		{
			cnt += (int)has[u];
			if (cnt == 1 && sz[v] == 2 * need)
			{
				printf("%d%s%d", v + 1, " ", last[u] + 1);
				return 0;
			}
			if (cnt == 2)
			{
				printf("%d%s%d", last_u + 1, " ", last[u] + 1);
				return 0;
			}
			last_u = has[u] ? last[u] : last_u;
		}
	}
	printf("%s", "-1");
	return 0;
}

