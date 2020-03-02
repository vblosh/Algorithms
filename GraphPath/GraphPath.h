#pragma once
#include <forward_list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

struct Edge
{
	Edge(int atarget, int alenght) : target(atarget), lenght(alenght) {}
	int target;
	int lenght;
};

struct Vertex
{
	char Name;
	forward_list<Edge> AdjacencyList;
	// Dijkstra
	int distance;
	int prev;
	~Vertex() { AdjacencyList.clear(); }
};

typedef vector<Vertex> Graph;
typedef vector<pair<int, int>> IntPair;

int DeleteMin(Graph& graph, vector<int>& minHeap)
{
	auto minIdx = std::min_element(minHeap.begin(), minHeap.end(), [&graph](auto lhv, auto rhv) { return graph[lhv].distance < graph[rhv].distance; });
	int result(*minIdx);
	auto newend = std::remove(minHeap.begin(), minHeap.end(), *minIdx);
	minHeap.erase(newend, minHeap.end());
	return result;
}

void DijkstraShotestPath(Graph& graph, int startIdx)
{
	vector<int> minHeap;
	for (Vertex& v: graph)
	{
		v.distance = INT_MAX;
		v.prev = -1;
	}

	graph[startIdx].distance = 0;
	minHeap.push_back(startIdx);

	while (!minHeap.empty())
	{
		int minElement = DeleteMin(graph, minHeap);
		Vertex& v = graph[minElement];
		for (Edge edge : v.AdjacencyList)
		{
			Vertex& u = graph[edge.target];
			if (u.distance == INT_MAX)
			{
				minHeap.push_back(edge.target);
			}
			if (u.distance > v.distance + edge.lenght)
			{
				u.prev = minElement;
				u.distance = v.distance + edge.lenght;
			}
		}
	}
}

void PrintEdges(std::ostream& stream, const Graph& graph)
{
	stream << "PrintEdges: " << endl;
	for (const Vertex& u : graph)
	{
		stream << u.Name << ':';
		for (Edge edge : u.AdjacencyList)
		{
			const Vertex& v = graph[edge.target];
			stream << u.Name << "->" << v.Name << ':' << edge.lenght << ", ";
		}
		stream << endl;
	}
}


void PrintPath(std::ostream& stream, const Graph& graph)
{
	stream << "PrintPath: " << endl;
	for (const Vertex& u : graph)
	{

		stream << u.Name << " prev is " << (u.prev == -1 ? '0' :graph[u.prev].Name)
			<< " distance=" << u.distance << endl;
	}
}

