#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

typedef int value;
typedef vector<value> arr;
const int NUM = 8;
const int MAX = 10;

int Partition(arr& data, int l, int r)
{
	value val = data[r];
	int i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (data[j] < val)
		{
			swap(data[i++], data[j]);
		}
	}
	swap(data[i], data[r]);
	return i;
}

void QuickSort(arr& data, int l, int r)
{
	if (l < r)
	{
		int q = Partition(data, l, r);
		QuickSort(data, l, q - 1);
		QuickSort(data, q + 1, r);
	}
}

ostream& operator << (ostream& stream, vector<value> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		stream << vec[i] << ' ';
	}
	stream << '\n';
	return stream;
}

int main()
{
	arr data(NUM);
	for (size_t i = 0; i < data.size(); i++)
	{
		data[i] = MAX * rand() / RAND_MAX;
	}

	QuickSort(data, 0, NUM - 1);
	cout << data;
	assert(std::is_sorted(data.begin(), data.end()));

	return 0;
}

