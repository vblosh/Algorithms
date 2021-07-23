/*
* ƒан массив из нулей и единиц. Ќужно определить, какой максимальный по длине подинтервал единиц можно получить, удалив ровно один элемент массива.
[1, 1, 0]
*/

#include <iostream>
#include <array>
#include <vector>
#include "FinderSM.h"

using namespace std;

// max subsequence = 7
std::vector<data_t> input = { 0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1,1 };

size_t prev_len, cur_len, max_len;

void init()
{
	prev_len = cur_len = max_len = 0;
}

void process_next(data_t& val)
{
	if (val == 0)
	{
		if (prev_len + cur_len > max_len)
			max_len = prev_len + cur_len;
		prev_len = cur_len;
		cur_len = 0;
	}
	else
	{
		++cur_len;
	}
}

void process_end()
{
	if (prev_len + cur_len > max_len)
		max_len = prev_len + cur_len;
}

int main()
{
	for (auto& val : input)
	{
		process_next(val);
	}
	process_end();

	std::cout << "The max subsequence = " << max_len << endl;
	return 0;
}


int main1()
{
	FinderSM sm;
	for (auto& val: input)
	{
		sm.process_next(val);
	}
	sm.process_end();

	std::cout << "The max subsequence = " << sm.get_max_length() << endl;
	return 0;
}
