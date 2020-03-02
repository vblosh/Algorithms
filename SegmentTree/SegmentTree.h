#pragma once
#include <vector>

using namespace std;
typedef int _T;

struct Node
{
	_T sum;
	Node* left;
	Node* right;
};

class SumSegmentTree
{
public:
	SumSegmentTree() : root(nullptr) {}
	~SumSegmentTree()
	{
		Free(root);
	}

	void build(vector<_T>& a)
	{
		size = a.size();
		root = new Node();
		do_build(a, root, 0, size - 1);
	}

	_T query(size_t l, size_t r)
	{
		return do_query(root, 0, size - 1, l, r);
	}

	void update(int pos, _T new_val)
	{
		do_update(root, 0, size - 1, pos, new_val);
	}

private:
	void do_build(vector<_T>& a, Node* p, size_t tl, size_t tr)
	{
		if (tl == tr)
		{
			p->sum = a[tl];
			p->left = nullptr;
			p->right = nullptr;
		}
		else
		{
			size_t tm = (tl + tr) / 2;
			p->left = new Node();
			p->right = new Node();
			do_build(a, p->left, tl, tm);
			do_build(a, p->right, tm + 1, tr);
			p->sum = combine(p->left->sum, p->right->sum);
		}
	}

	_T do_query(Node* p, size_t tl, size_t tr, size_t l, size_t r)
	{
		if (!p)
			return _T();

		if (tl == l && tr == r)
		{
			return p->sum;
		}
		else
		{
			size_t tm = (tl + tr) / 2;
			_T lres = do_query(p->left, tl, tm, l, __min(r, tm));
			_T rres = do_query(p->right, tm + 1, tr, __max(l, tm + 1), r);
			return lres + rres;
		}
	}

	void do_update(Node* p, int tl, int tr, int pos, _T new_val)
	{
		if (tl == tr)
			p->sum = new_val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				do_update(p->left, tl, tm, pos, new_val);
			else
				do_update(p->right, tm + 1, tr, pos, new_val);
			p->sum = combine(p->left->sum, p->right->sum);
		}
	}

	void Free(Node* p)
	{
		if (!p)
			return;
		Free(p->left);
		Free(p->right);
		delete p;
	}

	_T combine(_T a, _T b)
	{
		return a + b;
	}

	Node* root;
	size_t size;
};
