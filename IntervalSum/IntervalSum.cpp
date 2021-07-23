/*
Дан список интов и число-цель. Нужно найти такой range, чтобы сумма его элементов давала число-цель.

elements = [1, -3, 4, 5]

target = 9

result = range(2, 4) # because elements[2] + elements[3] == target
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <deque>
#include <assert.h>
#include <random>

#include "IntervalSum.h"

using namespace std;

std::deque<std::pair<int, int>> find_intervals(std::vector<int>& input, int target)
{
	vector<int> cumulative_sum;
	unordered_map<int, set<int>> seek_sums;
	std::deque<std::pair<int, int>> output;

	cumulative_sum.resize(input.size());
	cumulative_sum[0] = input[0];
	for (size_t i = 1; i < input.size(); ++i)
	{
		cumulative_sum[i] = cumulative_sum[i - 1] + input[i];
		seek_sums[cumulative_sum[i]].insert(i);
	}

	int start_cum_sum = 0;
	for (size_t i = 0; i < input.size(); ++i)
	{
		start_cum_sum += input[i];
		auto it = seek_sums.find(target + start_cum_sum);
		if (it != seek_sums.end())
		{
			auto it2 = it->second.upper_bound(i);
			for (; it2 != it->second.end(); ++it2)
			{
				// found
				assert(target == cumulative_sum[*it2] - cumulative_sum[i]);
				output.push_back({ i, *it2 });
			}
		}
	}
	return output;
}

int main()
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(-1000, 1000);

	vector<int> input(1000);
	for (size_t i = 0; i < input.size(); ++i)
	{
		input[i] = distrib(gen);
	}

	int target = 500;

	auto res = find_intervals(input, target);
	for (auto interval : res)
	{
		cout << "[" << interval.first << ", " << interval.second << "]\n";
	}
}
