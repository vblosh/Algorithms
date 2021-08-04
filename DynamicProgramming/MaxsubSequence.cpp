#include "stdafx.h"
#include "Header.h"

std::vector<int_arr> MaxSubSequence(int_arr& a, size_t N)
{
	int_arr d(N);	// partial solution
	int_arr prev(N);	// linked list of partial solution indexes
	for (size_t i = 0; i < N; i++)
	{
		d[i] = 1;
		prev[i] = -1;
		for (size_t j = 0; j < i; j++)
		{
			if (a[j] < a[i])
			{
				if (d[i] < d[j] + 1)
				{
					d[i] = d[j] + 1;
					prev[i] = j;
				}
			}
		}
	}

	std::vector<int_arr> max_sub_seq;
	int max_subs_len = d[N-1];
	for (size_t i = N-1; d[i] == max_subs_len; --i)
	{
		size_t idx = i;
		max_sub_seq.push_back(int_arr());
		do
		{
			max_sub_seq[max_sub_seq.size()-1].push_back(a[idx]);
			idx = prev[idx];
		} while (idx != -1);
		std::reverse(max_sub_seq[max_sub_seq.size() - 1].begin(), max_sub_seq[max_sub_seq.size() - 1].end());
	}

	return max_sub_seq;
}


