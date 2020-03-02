#include <iostream>
#include <string>
#include "DisjointSet.h"

using namespace std;

int main()
{
	int N;
	cin >> N;
	DisjointSet dsj(N*2+1);
	for (size_t i = 1; i <= 2 * N; i++)
	{
		dsj.make_set(i);
	}

	int G, B;
	for (size_t i = 0; i < N; i++)
	{
		cin >> G >> B;
		dsj.union_sets(G, B);
	}

	int min = 2 * N;
	int max = 0;
	int size;
	for (size_t i = 1; i <= 2 * N; i++)
	{
		size = dsj.get_size(i);
		if (size > 1 && size < min)
			min = size;
		if (size > max)
			max = size;
	}

	cout << min << ' ' << max;

	return 0;


	//int N, Q;
	//cin >> N >> Q;
	//
	//DisjointSet dsj(N);
	//for (size_t i = 1; i <= N; i++)
	//{
	//	dsj.make_set(i);
	//}

	//string cmd;
	//int I, J;
	//for (size_t i = 0; i < Q; i++)
	//{
	//	cin >> cmd;
	//	if (cmd == "M")
	//	{
	//		cin >> I >> J;
	//		dsj.union_sets(I, J);
	//	}
	//	else
	//	{
	//		cin >> I;
	//		cout << dsj.get_size(I) << endl;
	//	}
	//}

 //   return 0;
}

