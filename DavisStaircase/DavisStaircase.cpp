// DavisStaircase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

array<int, 3> steps = { 1, 2, 3 };

unordered_map<int, int> memo;

int TryClimb(int height)
{
	if (memo.find(height) != memo.end())
		return memo[height];

	int numCases = 0;

	for (int step : steps)
	{
		int diff = height - step;
		if (diff < 0)
			break;
		if (diff < 0)
			break;
		if (diff == 0)
			numCases++;
		else
			numCases += TryClimb(diff);
	}

	memo[height] = numCases;
	return numCases;
}

int main()
{
	int N;
	cin >> N;
	vector<int> arr(N);
	for (size_t i = 0; i < arr.size(); i++)
	{
		cin >> arr[i];
	}

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);

	for (int height : arr)
	{
		cout << TryClimb(height) << endl;
	}

	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	cout << "Total " << double(end.QuadPart - start.QuadPart)*1000.0 / freq.QuadPart << "ms\n";

    return 0;
}

