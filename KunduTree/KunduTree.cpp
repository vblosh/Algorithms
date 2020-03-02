#include <iostream>
#include <vector>
#include <string>
#include <forward_list>

using namespace std;

struct Vertex
{
	Vertex() : Visited(false) {}
	std::forward_list<int> AdjacencyList;
	bool Visited;
};

typedef vector<Vertex> Graph;

void Explore(Graph& graph, int graph_index, int& current_bad_subtree_size)
{
	graph[graph_index].Visited = true;
	current_bad_subtree_size++;
	for(int siblings : graph[graph_index].AdjacencyList)
	{
		if (!graph[siblings].Visited)
		{
			Explore(graph, siblings, current_bad_subtree_size);
		}
	}
}

void DepthFirstSearch(Graph& graph, vector<int>& bad_subtrees)
{
	for (size_t i = 1; i < graph.size(); i++)
	{
		int current_bad_subtree_size = 0;
		if (!(graph[i].Visited || graph[i].AdjacencyList.empty()))
		{
			Explore(graph, i, current_bad_subtree_size);
			if (current_bad_subtree_size > 0)
			{
				bad_subtrees.push_back(current_bad_subtree_size);
			}
		}
	}
}

int main()
{
	long long N;
	cin >> N;
	// build tree
	std::vector<Vertex> tree(N+1); // we using 1 indexing
	int start, end;
	string color;
	for (size_t i = 0; i < N-1; i++)
	{
		cin >> start >> end >> color;
		if (color == "b")
		{
			tree[start].AdjacencyList.push_front(end);
			tree[end].AdjacencyList.push_front(start);
		}
	}
	// find all bad subtrees
	std::vector<int> bad_subtrees;
	DepthFirstSearch(tree, bad_subtrees);
	// calculate 
	long long good = N*(N - 1)*(N - 2) / 6;
	long long bad = 0;
	for (size_t i = 0; i < bad_subtrees.size(); i++)
	{
		long long ti = bad_subtrees[i];
		bad += ti*(ti - 1)*(3 * N - 2 * ti - 2)/6;
	}
	good -= bad;

	const long long MAX_RES = 1000000000 + 7;
	if (good > MAX_RES)
		cout << good % MAX_RES;
	else
		cout << good;

    return 0;
}

