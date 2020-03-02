#include <iostream>
#include <string>

using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
};

void preOrder(node *p) {
	cout << p->data << ' ';
	if (p->left)
		preOrder(p->left);
	if (p->right)
		preOrder(p->right);
}

void postOrder(node *p) {
	if (p->left)
		preOrder(p->left);
	if (p->right)
		preOrder(p->right);
	cout << p->data << ' ';
}

void inOrder(node *p) {
	if (p->left)
		inOrder(p->left);
	cout << p->data << ' ';
	if (p->right)
		inOrder(p->right);
}



int main()
{
    return 0;
}

