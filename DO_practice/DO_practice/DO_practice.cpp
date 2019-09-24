// DO_practice.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
	node *l, *r;
	int val;
	int prior;

	node() {}
	node(int _val)
	{
		l = nullv;
		r = nullv;
		val = _val;
		prior = rand();
	}
};

pair<node*, node*> split(node *t, int val)
{
	if (t == nullv)
	{
		return{ nullv, nullv };
	}
	else if (t->val < val)
	{
		pair<node*, node*> ret = split(t->r, val);
		t->r = ret.first;
		return{ t, ret.second };
	}
	else
	{
		pair<node*, node*> ret = split(t->l, val);
		t->l = ret.second;
		return{ ret.first, t };
	}
}

node* merge(node *l, node *r)
{
	if (l == nullv)
	{
		return r;
	}
	if (r == nullv)
	{
		return l;
	}
	if (l->prior > r->prior)
	{
		l->r = merge(l->r, r);
		return l;
	}
	else
	{
		r->l = merge(l, r->l);
		return r;
	}
}

node *t;

node *nullv;

int main()
{
	return 0;
}

