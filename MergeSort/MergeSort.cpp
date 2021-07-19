#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

const int NUM = 1000;

typedef int Typ;
typedef vector<Typ> arr;
long long g_inversions = 0;

void Merge(Typ* data, Typ* temp, int l, int m, int r)
{
	int lsize = m - l + 1;
	int rsize = r - m;
	int lidx = l;
	int ridx = m + 1;
	for (int i = l; i <= r; i++)
	{
		if (lidx < (m + 1) && ridx <= r)
		{
			if (data[lidx] <= data[ridx])
			{
				temp[i] = data[lidx++];
			}
			else
			{
				g_inversions += (m + 1) - lidx;
				temp[i] = data[ridx++];
			}
		}
		else
		{
			if (lidx < (m + 1))
			{
				g_inversions += (m + 1) - lidx;
				temp[i] = data[lidx++];
			}
			else if (ridx <= r)
			{
				temp[i] = data[ridx++];
			}
		}
	}
	for (int i = l; i <= r; i++)
	{
		data[i] = temp[i];
	}
}

void MergeSort(Typ* data, Typ* temp, int l, int r)
{
	if (l == r)
		return;

	int m = (l + r) / 2;
	// divide
	MergeSort(data, temp, l, m);
	MergeSort(data, temp, m + 1, r);
	// conquer
	Merge(data, temp, l, m, r);
}

int main()
{
	arr data(NUM);
	for (size_t i = 0; i < data.size(); i++)
	{
		data[i] = rand();
	}

	arr temp(NUM);

	MergeSort(&data[0], &temp[0], 0, data.size() - 1);
	assert(std::is_sorted(data.begin(), data.end()));

	return 0;

	//int N;
	//cin >> N;
	//arr data(N);
	//for (size_t i = 0; i < data.size(); i++)
	//{
	//	cin >> data[i];
	//}

	//arr temp(N);

	//MergeSort(&data[0], &temp[0], 0, data.size() - 1);
	//assert(std::is_sorted(data.begin(), data.end()));

	return 0;
}

