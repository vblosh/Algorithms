/*
Слияние отрезков:

Вход: [1, 3] [100, 200] [2, 4]
Выход: [1, 4] [100, 200]
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<pair<int, int>> input = { {1, 3}, {100, 200}, {2, 4} };

int main()
{
    sort(input.begin(), input.end(), [](auto& left, auto& right) { return left.first < right.first;  });

	int start = input[0].first;
	int end = input[0].second;
	for (size_t i = 1; i < input.size(); i++)
	{
		if (input[i].first <= end)
		{
			end = max(end, input[i].second);
		}
		else
		{
			// print output
			cout << "[" << start << ", " << end << "] ";
			// new interval
			start = input[i].first;
			end = input[i].second;
		}
	}
	cout << "[" << start << ", " << end << "]\n";
}

