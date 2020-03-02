#include <iostream>
#include <istream>
#include "GraphDecomposition.h"

using namespace std;

// Format
// N num nodes
// for each node M - num egdes, A - Name, a list E1 E2 E3 - adjacency list with edges
void InitGraph(Graph& graph)
{
	int N;
	cin >> N;
	graph.resize(N);
	for (int i = 0; i < N; i++)
	{
		int num_edges;
		cin >> num_edges;
		cin >> graph[i].Name;
		int edge;
		for (int j = 0; j < num_edges; j++)
		{
			cin >> edge;
			graph[i].AdjacencyList.push_front(edge);
		}
	}
}

void InitGraph1(Graph& graph)
{
	graph.resize(4);
	graph[0].Name = 'A'; graph[0].AdjacencyList.push_front(1); graph[0].AdjacencyList.push_front(3); 
	graph[1].Name = 'B'; graph[1].AdjacencyList.push_front(2); graph[1].AdjacencyList.push_front(3); 
	graph[2].Name = 'C'; graph[2].AdjacencyList.push_front(0); 
	graph[3].Name = 'D'; graph[3].AdjacencyList.push_front(2); 
}

void InitGraph2(Graph& graph)
{
	graph.resize(8);
	graph[0].Name = 'A'; graph[0].AdjacencyList.push_front(2);
	graph[1].Name = 'B'; graph[1].AdjacencyList.push_front(2);
	graph[2].Name = 'C'; graph[2].AdjacencyList.push_front(3); graph[2].AdjacencyList.push_front(4);
	graph[3].Name = 'D'; graph[3].AdjacencyList.push_front(5); 
	graph[4].Name = 'E'; graph[4].AdjacencyList.push_front(5); 
	graph[5].Name = 'F'; graph[5].AdjacencyList.push_front(6); graph[5].AdjacencyList.push_front(7);
	graph[6].Name = 'G';
	graph[7].Name = 'H';
}

void InitGraph4(Graph& graph)
{
	graph.resize(12);
	graph[0].Name = 'A'; graph[0].AdjacencyList.push_front(1); 
	graph[1].Name = 'B'; graph[1].AdjacencyList.push_front(2); graph[1].AdjacencyList.push_front(3); graph[1].AdjacencyList.push_front(4);
	graph[2].Name = 'C'; graph[2].AdjacencyList.push_front(5); 
	graph[3].Name = 'D';
	graph[4].Name = 'E'; graph[4].AdjacencyList.push_front(1); graph[4].AdjacencyList.push_front(5); graph[4].AdjacencyList.push_front(6);
	graph[5].Name = 'F'; graph[5].AdjacencyList.push_front(2); graph[5].AdjacencyList.push_front(7);
	graph[6].Name = 'G'; graph[6].AdjacencyList.push_front(7); graph[6].AdjacencyList.push_front(9);
	graph[7].Name = 'H'; graph[7].AdjacencyList.push_front(10); 
	graph[8].Name = 'I'; graph[8].AdjacencyList.push_front(6); 
	graph[9].Name = 'J'; graph[9].AdjacencyList.push_front(8);
	graph[10].Name = 'K'; graph[10].AdjacencyList.push_front(11);
	graph[11].Name = 'L'; graph[11].AdjacencyList.push_front(9);
}



int main()
{
	Graph graph;
	InitGraph(graph);

	if (false)
	{
		DepthFirstSearch(graph);

		PrintPrePost(cout, graph);

		PrintEdges(cout, graph);

		PrintConnectedComponent(cout, graph);

		TopologicalSort(cout, graph);
	}
	else
	{
		BuildMetaGraph(graph);

		PrintEdges(cout, graph);

		PrintConnectedComponent(cout, graph);
	}

    return 0;
}

