#include <iostream>
#include "GraphPath.h"

void InitGraph1(Graph& graph)
{
	graph.resize(5);
	graph[0].Name = 'A'; graph[0].AdjacencyList.push_front(Edge(1, 4)); graph[0].AdjacencyList.push_front(Edge(2, 2));
	graph[1].Name = 'B'; graph[1].AdjacencyList.push_front(Edge(2, 3)); graph[1].AdjacencyList.push_front(Edge(3, 2)); graph[1].AdjacencyList.push_front(Edge(4, 3));
	graph[2].Name = 'C'; graph[2].AdjacencyList.push_front(Edge(1, 1)); graph[2].AdjacencyList.push_front(Edge(3, 4)); graph[2].AdjacencyList.push_front(Edge(4, 5));
	graph[3].Name = 'D'; 
	graph[4].Name = 'E'; graph[4].AdjacencyList.push_front(Edge(3, 1)); 
}

int main()
{
	Graph graph;
	InitGraph1(graph);

	PrintEdges(cout, graph);

	DijkstraShotestPath(graph, 0);

	PrintPath(cout, graph);

    return 0;
}

