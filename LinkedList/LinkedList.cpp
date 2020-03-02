// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

struct Node
{
	Node(int d) : data(d), next(nullptr) {}
	int data;
	struct Node *next;
};

void Traverse(Node* head, function<void(Node*)> fn)
{
	Node* p = head;
	while (p)
	{
		fn(p);
		p = p->next;
	}
}

void PrintList(Node* head)
{
	Traverse(head, [](auto p) { cout << p->data << "->"; });
	cout << "NULL\n";
}

Node* AddHead(Node* head, int d)
{
	Node* new_node = new Node(d);
	new_node->next = head;
	head = new_node;
	return head;
}

Node* ReadList(Node* head)
{
	int N;
	cin >> N;
	for (size_t i = 0; i < N; i++)
	{
		int d;
		cin >> d;
		head = AddHead(head, d);
	}
	return head;
}

Node* Reverse(Node *head)
{
	Node* curr = head;
	Node* prev = nullptr;
	while (curr && curr->next) {
		Node* next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	if (curr)
		curr->next = prev;
	return curr;
}

bool has_cycle(Node* head) {
	Node* slow = head;
	Node* fast = head;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) {
			return true;
		}
	}

	return false;
}

int FindMergeNode(Node *pA, Node *pB)
{
	vector<int> A;
	while (pA) {
		A.push_back(pA->data);
		pA = pA->next;
	}

	vector<int> B;
	while (pB) {
		B.push_back(pB->data);
		pB = pB->next;
	}

	int iA = A.size() - 1;
	int iB = B.size() - 1;
	while (A[iA] == B[iB])
	{
		iA--;
		iB--;
	}

	return A[++iA];
}

int main()
{
	int PN;
	cin >> PN;
	for (size_t i = 0; i < PN; i++)
	{
		Node* head = ReadList(nullptr);
		PrintList(head);
		head = Reverse(head);
		PrintList(head);
	}

    return 0;
}

