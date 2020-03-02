#include <iostream>
#include <vector>
#include "AVLTree.h"

using namespace std;

AVLtree<int> t;

void calc_median(AVLnode<int>* root)
{
	if (root->balance == 0)
		printf("%d\n", root->key);
	else if(root->balance == -1)
	{
		long long s1 = long long(root->key) + long long(root->left->key);
		if(s1 % 2 == 1)
			printf("%.1f\n", s1 / 2.0);
		else
			printf("%.0f\n", s1 / 2.0);
	}
	else //if (root->balance == 1)
	{
		long long s1 = long long(root->key) + long long(root->right->key);
		if (s1 % 2 == 1)
			printf("%.1f\n", s1 / 2.0);
		else
			printf("%.0f\n", s1 / 2.0);
	}
}

void median(char cmd, int x) 
{
	if (cmd == 'r')
	{
		if (t.find_key(x))
		{
			t.delete_key(x);
			if(t.Root())
				calc_median(t.Root());
			else
				printf("Wrong!\n");
		}
		else
			printf("Wrong!\n");
	}
	else
	{
		t.insert(x);
		calc_median(t.Root());
	}
}

int main(void) {

	//Helpers for input and output
	int N;
	cin >> N;

	char cmd;
	int x;
	for (int i = 0; i < N; i++) {
		cin >> cmd >> x;
		median(cmd, x);
	}

	return 0;
}


//int main(void)
//{
//	AVLtree<int> t;
//
//	std::cout << "Inserting integer values 1 to 10" << std::endl;
//	for (int i = 1; i <= 10; ++i)
//		t.insert(i);
//
//	std::cout << "Printing balance: ";
//	t.printBalance();
//}
