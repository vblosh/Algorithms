#include "stdafx.h"
#include "Header.h"

// Input:
// Weights (stored in array w)
// Values (stored in array v)
// Number of distinct items (n)
// Knapsack capacity (W)
std::pair<int, int_arr> KnapSackUnbounded(int_arr& w, int_arr& v, int n, int W)
{
	int_arr K(W + 1);
	int_arr KW(W + 1);
	K[0] = 0;
	KW[0] = -1;
	for (int iw = 1; iw <= W; iw++)
	{
		int max = INT_MIN;
		size_t max_idx = -1;
		for (size_t i = 0; i < n; i++)
		{
			if (w[i] <= iw)
			{
				if (max < K[iw - w[i]] + v[i])
				{
					max = K[iw - w[i]] + v[i];
					max_idx = i;
				}
			}
		}
		if (max_idx != -1)
		{
			K[iw] = max;
			KW[iw] = w[max_idx];
		}
	}

	int_arr things;
	int idx = W;
	do
	{
		things.push_back(KW[idx]);
		idx -= KW[idx];

	} while (idx > 0);
	return std::make_pair(K[W], things);
}

// Input:
// Weights (stored in array w)
// Values (stored in array v)
// Number of distinct items (n)
// Knapsack capacity (W)
int KnapSack(int_arr& w, int_arr& v, int n, int W)
{
	std::vector<int_arr> K(n+1, int_arr(W + 1));
	for (size_t j = 1; j <= n; j++)
	{
		for (size_t iw = 0; iw <= W; iw++)
		{
			if (w[j-1] > iw)
			{
				K[j][iw] = K[j - 1][iw];
			}
			else
			{
				K[j][iw] = __max(K[j - 1][iw], K[j - 1][iw - w[j-1]] + v[j-1]);
			}
		}
	}
	return K[n][W];
}
