#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

typedef int value;

struct Node
{
	Node(value avalue) : value(avalue), visited(false) {}
	value value;
	bool visited;
	vector<Node*> children;
};

Node* InitTree3()
{
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	n1->children.push_back(n2);
	n1->children.push_back(n4);
	n2->children.push_back(n3);
	n3->children.push_back(n1);
	return n1;
}


void DepthFirstSearch(Node* node, int level, function<void(Node*, int)> preVisit, function<void(Node*, int)> postVisit)
{
	if(preVisit) preVisit(node, level);

	node->visited = true;
	for (Node* child : node->children)
	{
		if(!child->visited)
			DepthFirstSearch(child, level + 1, preVisit, postVisit);
	}

	if (postVisit) postVisit(node, level);
}

void BreadthFirstSearch(Node* node, int level, function<void(Node*, int)> preVisit, function<void(Node*, int)> postVisit)
{
	static queue<tuple<Node*, int>> to_visiting;

	if (preVisit) preVisit(node, level);

	node->visited = true;
	for (Node* child : node->children)
	{
		if (!child->visited)
			to_visiting.push(make_tuple(child, level + 1));
	}

	if (postVisit) postVisit(node, level);

	while (!to_visiting.empty())
	{
		auto next = to_visiting.front();
		to_visiting.pop();
		BreadthFirstSearch(get<0>(next), get<1>(next), preVisit, postVisit);
	}
}

int main()
{
	int max_depth = 0;
	int* mptr = &max_depth;
	Node* root = InitTree3();

	cout << endl << "DepthFirstSearch" << endl;
	DepthFirstSearch(root, 0, 
	[](Node* node, int level)
	{
		cout << "pre visiting node " << node->value << " at level " << level << endl;
	},
	[mptr](Node* node, int level)
	{
		cout << "post visiting node " << node->value << " at level " << level << endl;
		*mptr = max(*mptr, level);
		delete node;
	});

	root = InitTree3();
	cout  << endl << "BreadthFirstSearch" << endl;
	BreadthFirstSearch(root, 0,
	[](Node* node, int level)
	{
		cout << "pre visiting node " << node->value << " at level " << level << endl;
	},
	[](Node* node, int level)
	{
		cout << "post visiting node " << node->value << " at level " << level << endl;
		delete node;
	});

    return 0;
}

