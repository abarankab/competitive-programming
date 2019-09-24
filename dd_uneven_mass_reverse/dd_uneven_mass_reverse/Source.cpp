#include <iostream>
#include <random>
#include <time.h>
#include <string>

using namespace std;

random_device seed;
mt19937_64 mersenne(seed());

struct node {
	bool to;
	int sz;
	long long prior;
	char val;
	node *l, *r;

	node() {}

	node(char _val) {
		val = _val;
		prior = mersenne();
		sz = 1;
		l = NULL;
		r = NULL;
		to = 0;
	}
};

int sz(node *t) {
	if (t) return t->sz;
	return 0;
}

void push(node *t) {
	if (!t) return;

	if (t->to) {
		swap(t->l, t->r);
		if (t->l) {
			t->l->to ^= 1;
		}
		if (t->r) {
			t->r->to ^= 1;
		}
		t->to = 0;
	}
}

void recalc(node *t) {
	if (t) {
		t->sz = 1;
		if (t->l) t->sz += sz(t->l);
		if (t->r) t->sz += sz(t->r);
	}
}

void split(node *t, node *&l, node *&r, int id) {
	if (!t) {
		l = r = NULL;
		return;
	}

	push(t);
	if (sz(t->l) >= id) {
		split(t->l, l, t->l, id);
		r = t;
	}
	else {
		split(t->r, t->r, r, id - sz(t->l) - 1);
		l = t;
	}
	recalc(l);
	recalc(r);
}

void merge(node *&t, node *l, node *r) {
	if (!l) { t = r;  return; }
	if (!r) { t = l; return; }

	push(l);
	push(r);

	if (l->prior > r->prior) {
		merge(l->r, l->r, r), t = l;
	}
	else {
		merge(r->l, l, r->l), t = r;
	}

	recalc(t);
}

void insert(node *&t, char c) {
	node *nw = new node(c);
	merge(t, t, nw);
}

void reverse(node *t, int i, int j) {
	node *l, *r, *m;
	split(t, l, r, i);
	split(r, m, r, j - i + 1);
	m->to ^= 1;
	merge(r, m, r);
	merge(t, l, r);
}

char get(node *t, int id) {
	node *l, *r, *m;
	split(t, l, r, id);
	split(r, m, r, 1);
	char res = m->val;
	merge(r, m, r);
	merge(t, l, r);
	return res;
}

void print(node *t) {
	push(t);
	if (t->l) print(t->l);
	cout << t->val;
	if (t->r) print(t->r);
}

node *t;
int n, m, ii, jj;
char c, tp;
string res;

signed main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> n >> ii >> jj;
	--ii, --jj;
	for (int i = 0; i < n; ++i) {
		cin >> c;
		insert(t, c);
	}
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> tp;
		if (tp == 'R') {
			reverse(t, ii, jj);
		}
		else if (tp == 'Q') {
			cin >> tp;
			if (tp == 'L') res += get(t, ii);
			else res += get(t, jj);
		}
		else if (tp == 'S') {
			cin >> tp;
			if (tp == 'L') {
				cin >> tp;
				if (tp == 'L') --ii;
				else ++ii;
			}
			else {
				cin >> tp;
				if (tp == 'L') --jj;
				else ++jj;
			}
		}
	}
	cout << res << endl;
	return 0;
}