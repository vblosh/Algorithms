// RunningMedian.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "Heap.h"

using namespace std;

int main() {
	int n;
	cin >> n;

	//priority_queue<int, vector<int>, less<int>> left;
	//priority_queue<int, vector<int>, greater<int>> right;
	heap<int, less<int>> left;
	heap<int, greater<int>> right;

	int cur;
	cout.precision(1);
	cout << fixed;
	for (int a_i = 0; a_i < n; a_i++) 
	{
		cin >> cur;
		if (left.empty())
		{
			left.add(cur);
		}
		else
		{
			if (cur <= left.top())
			{
				left.add(cur);
			}
			else
			{
				right.add(cur);
			}

			// balance heaps
			if (left.size() > right.size() + 1)
			{
				right.add(left.top());
				left.remove_top();
			}
			if (right.size() > left.size())
			{
				left.add(right.top());
				right.remove_top();
			}
		}

		double median = left.size() == right.size() ? (left.top() + right.top())*(1.0 / 2.0) : left.top();
		cout << median << endl;
	}

	return 0;
}
