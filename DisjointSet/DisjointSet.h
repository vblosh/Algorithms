#pragma once
#include <vector>

class DisjointSet
{
public:
	DisjointSet(int asize)
	{
		parent.resize(asize + 1);
		size.resize(asize + 1);
	}

	void make_set(int v)
	{
		parent[v] = v;
		size[v] = 1;
	}

	void union_sets(int a, int b)
	{
		a = find_set(a);
		b = find_set(b);
		if (a != b) {
			if (size[a] < size[b])
				std::swap(a, b);
			parent[b] = a;
			size[a] += size[b];
		}
	}

	int find_set(int v)
	{
		if (v == parent[v])
			return v;
		return parent[v] = find_set(parent[v]);
	}

	int get_size(int v)
	{
		return size[find_set(v)];
	}

private:
	std::vector<int> parent;
	std::vector<int> size;
};
