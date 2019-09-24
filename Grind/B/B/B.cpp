// B.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <random>

using namespace std;

struct node
{
	node *l, *r;
	int ind, key;

	node() {}
	node(int _ind)
	{
		ind = _ind;
		key = rand();
		l = nullptr;
		r = nullptr;
	}
};

node *merge(node *a, node *b)
{
	if (a->key > b->key)
	{
		return a->r = merge(a->r, b);
	}
	else
	{
		return b->l = merge(a, b->l);
	}
}

pair<node*, node*> split(node *t, int key)
{
	if (!t)
	{
		return{ nullptr, nullptr };
	}
	if ()
}

int main()
{
    return 0;
}

