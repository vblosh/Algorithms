// DynamicProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"

using namespace std;

template<class _Ty>
ostream& operator << (ostream& stream, std::vector<_Ty, std::allocator<_Ty>> vec)
{
	stream << '[' << vec.size() << "]{";
	if (vec.size() > 0)
	{
		for (size_t i = 0; i < vec.size() - 1; i++)
		{
			stream << vec[i] << ',';
		}
		stream << vec[vec.size() - 1];
	}
	stream <<  '}';
	return stream;
}

int main()
{
	size_t N;
	cin >> N;	// size of sequence
	int_arr arr(N); // sequence
	for (size_t i = 0; i < arr.size(); i++)
	{
		cin >> arr[i];
	}

	cout << "max SubSequince is " << MaxSubSequince(arr, N) << endl;

	cin >> N;	// num of items
	int_arr w(N); // weight of item[i]
	int_arr v(N); // cost of item[i]
	for (size_t i = 0; i < N; i++)
	{
		cin >> w[i] >> v[i];
	}
	int W; // volume of ruecksack
	cin >> W;

	auto res = KnapSackUnbounded(w, v, N, W);
	cout << "max cost of the knapsack with repeated things is " << res.first << " {" << res.second << '}' << endl;

	auto cnt = KnapSack(w, v, N, W);
	cout << "max cost of the knapsack  " << cnt << endl;
	return 0;
}

