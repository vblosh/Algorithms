// ShortestPathInGraph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

struct Vertex
{
	Vertex(int id) : Id(id), Distance(-1) {}
	int Id;
	forward_list<int> AdjacencyList;
	int Distance;
};

class Graph 
{
	vector<Vertex> _nodes;
public:
	Graph(int n) 
	{
		_nodes.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_nodes.push_back(Vertex(i));
		}
	}
	
	void add_edge(int u, int v) 
	{
		if(find(_nodes[u].AdjacencyList.cbegin(), _nodes[u].AdjacencyList.cend(), v) == _nodes[u].AdjacencyList.end())
			_nodes[u].AdjacencyList.push_front(v);
		if (find(_nodes[v].AdjacencyList.cbegin(), _nodes[v].AdjacencyList.cend(), u) == _nodes[v].AdjacencyList.end())
			_nodes[v].AdjacencyList.push_front(u);
	}

	vector<int> shortest_reach(int start) 
	{
		BreadthFirstSearch(start);

		vector<int> res;
		for (auto node : _nodes)
		{
			res.push_back(node.Distance);
		}
		return res;
	}

	Vertex& Node(int id)
	{
		return _nodes[id];
	}

private:
	void BreadthFirstSearch(int start)
	{
		queue<int> queue;
		Node(start).Distance = 0;
		queue.push(start);

		while (!queue.empty())
		{
			int id = queue.front();
			queue.pop();
			for (int childId : Node(id).AdjacencyList)
			{
				if (Node(childId).Distance == -1)
				{
					Node(childId).Distance = Node(id).Distance + 1;
					queue.push(childId);
				}
			}
		}
	}
};

int main() {
	int queries;
	cin >> queries;

	for (int t = 0; t < queries; t++) {

		int n, m;
		cin >> n;
		// Create a graph of size n where each edge weight is 6: 
		Graph graph(n);
		cin >> m;
		// read and set edges
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			// add each edge to the graph
			graph.add_edge(u, v);
		}
		int startId;
		cin >> startId;
		startId--;
		// Find shortest reach from node s
		vector<int> distances = graph.shortest_reach(startId);

		for (int i = 0; i < distances.size(); i++) {
			if (i != startId) {
				int dist = distances[i] == -1 ? -1 : distances[i] * 6;
				cout << dist << " ";
			}
		}
		cout << endl;
	}

	return 0;
}
