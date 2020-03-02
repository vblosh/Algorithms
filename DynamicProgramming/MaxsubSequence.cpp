#include "stdafx.h"
#include "Header.h"

int_arr MaxSubSequince(int_arr& a, size_t N)
{
	int_arr d(N);
	int_arr prev(N);
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

	int_arr max_sub_seq;
	int max_idx = 0;
	for (size_t i = 1; i < N; i++)
	{
		if (d[i] > d[max_idx])
		{
			max_idx = i;
		}
	}

	int idx = max_idx;
	do
	{
		max_sub_seq.push_back(a[idx]);
		idx = prev[idx];
	} while (idx != -1);
	std::reverse(max_sub_seq.begin(), max_sub_seq.end());

	return max_sub_seq;
}


