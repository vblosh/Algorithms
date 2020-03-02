#pragma once
#include <forward_list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Vertex
{
	char Name;
	forward_list<int> AdjacencyList;
	bool Visited;
	int PreStep;
	int PostStep;
	int ConnectedComponentNum;
	~Vertex() { AdjacencyList.clear(); }
};

typedef vector<Vertex> Graph;
typedef vector<pair<int, int>> IntPair;

void Previsit(Graph& graph, int v, int& clock, int ccnum)
{
	graph[v].ConnectedComponentNum = ccnum;
	graph[v].PreStep = (clock++);
}

void Postvisit(Graph& graph, int v, int& clock, int ccnum)
{
	graph[v].PostStep = (clock++);
}

void Explore(Graph& graph, int v, int& clock, int ccnum)
{
	graph[v].Visited = true;
	Previsit(graph, v, clock, ccnum);
	for (int u : graph[v].AdjacencyList)
	{
		if (!graph[u].Visited)
			Explore(graph, u, clock, ccnum);
	}
	Postvisit(graph, v, clock, ccnum);
}

void DepthFirstSearch(Graph& graph)
{
	int currentConnectedComponentNum = 1;
	int clock = 1;
	for (size_t i = 0; i < graph.size(); i++)
	{
		if (!graph[i].Visited)
		{
			Explore(graph, i, clock, currentConnectedComponentNum);
			currentConnectedComponentNum++;
		}
	}
}

void TopologicalSort(std::ostream& stream, Graph& graph)
{
	DepthFirstSearch(graph);
	int count = graph.size();

	IntPair sortVector(count);
	for (int i = 0; i < count; i++)
	{
		sortVector[i].first = i;
		sortVector[i].second = graph[i].PostStep;
	}
	sort(sortVector.begin(), sortVector.end(), [](auto left, auto right) -> bool { return left.second > right.second; });

	stream << "Topological Sort: ";
	for (auto iter : sortVector)
		stream << graph[iter.first].Name << "->";
	stream << endl;
}

void PrintEdges(std::ostream& stream, const Graph& graph)
{
	stream << "PrintEdges: " << endl;
	for (const Vertex& u : graph)
	{
		stream << u.Name << ':';
		for (int childIdx : u.AdjacencyList)
		{
			const Vertex& v = graph[childIdx];
			stream << u.Name << "->" << v.Name;
			if (u.PreStep < v.PreStep && v.PostStep < u.PostStep)
			{
				stream << " tree, ";
			}
			else if (u.PreStep > v.PreStep && u.PostStep < v.PostStep)
			{
				stream << " back, ";
			}
			else if (v.PostStep < u.PreStep)
			{
				stream << " cross, ";
			}
		}
		stream << endl;
	}
}

void PrintPrePost(std::ostream& stream, const Graph& graph)
{
	stream << "PrintPrePost: " << endl;
	for (const Vertex& u : graph)
	{
		stream << "Vertex " << u.Name << " Pre = " << u.PreStep << "\tPost = " << u.PostStep << endl;
	}
}

void PrintConnectedComponent(std::ostream& stream, const Graph& graph)
{
	int count = graph.size();
	IntPair sortVector(count);
	for (int i = 0; i < count; i++)
	{
		sortVector[i].first = i;
		sortVector[i].second = graph[i].ConnectedComponentNum;
	}
	sort(sortVector.begin(), sortVector.end(), [](auto left, auto right) -> bool { return left.second < right.second; });

	stream << "Connected Components: ";
	int ccnum = 0;
	for (auto iter : sortVector)
	{
		if (graph[iter.first].ConnectedComponentNum != ccnum)
		{
			ccnum = graph[iter.first].ConnectedComponentNum;
			stream << "\nComponent " << ccnum << ':' << graph[iter.first].Name << ',';
		}
		else
		{
			stream << graph[iter.first].Name << ',';
		}
	}
	stream << endl;
}

Graph InverseGraph(const Graph& graph)
{
	Graph result;
	result.resize(graph.size());
	for (size_t i = 0; i < graph.size(); i++)
	{
		const Vertex& v = graph[i];
		result[i].Name = v.Name;
		// inverse edges
		for (int dst : v.AdjacencyList)
		{
			result[dst].AdjacencyList.push_front(i);
		}
	}
	return result;
}

void BuildMetaGraph(Graph& graph)
{
	int count = graph.size();
	Graph invGraph = InverseGraph(graph);
	DepthFirstSearch(invGraph);

	IntPair sortVector(count);
	for (int i = 0; i < count; i++)
	{
		sortVector[i].first = i;
		sortVector[i].second = invGraph[i].PostStep;
	}
	sort(sortVector.begin(), sortVector.end(), [](auto left, auto right) -> bool { return left.second > right.second; });

	int currentConnectedComponentNum = 1;
	int clock = 1;
	for (size_t i = 0; i < sortVector.size(); i++)
	{
		if (!graph[sortVector[i].first].Visited)
		{
			Explore(graph, sortVector[i].first, clock, currentConnectedComponentNum);
			currentConnectedComponentNum++;
		}
	}
}


