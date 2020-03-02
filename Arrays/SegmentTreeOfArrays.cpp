#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits.h>

using namespace std;

typedef unsigned int typ;
vector<vector<typ>> t;

void build(typ a[], int v, int tl, int tr) {
	if (tl == tr)
		t[v] = vector<typ>(1, a[tl]);
	else {
		int tm = (tl + tr) / 2;
		build(a, v * 2, tl, tm);
		build(a, v * 2 + 1, tm + 1, tr);
		merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(),
			back_inserter(t[v]));
	}
}


pair<int, int> combine(pair<typ, typ> p1, pair<typ, typ> p2)
{
	return make_pair(p1.first + p2.first, p1.second + p2.second);
}

pair<typ, typ> query(int v, int tl, int tr, int l, int r) {
	if (l >= r )
		return make_pair(0, 0);
	if (l == tl && tr == r) {
		return make_pair(t[v][0], t[v][1]);
	}
	int tm = (tl + tr) / 2;
	return combine(query(v * 2, tl, tm, l, min(r, tm)),
		query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int S(pair<typ, typ> p)
{
	return (((p.first & p.second) ^ (p.first | p.second)) & (p.first ^ p.second));
}

int main() {
	int n;
	cin >> n;
	vector<typ> a(n);
	t.resize(4 * n);

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	build(&a[0], 1, 0, n - 1);

	int ans = 0;
	int max = INT_MIN;
	for (size_t i = 1; i < a.size(); i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			pair<typ, typ> q = query(1, 0, n - 1, j, i);
			int res = S(q);
			if (res > max)
				max = res;
		}
	}
	cout << max << endl;

	return 0;
}