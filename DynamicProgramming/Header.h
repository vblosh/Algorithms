#pragma once

using int_arr = std::vector<int>;

int_arr MaxSubSequince(int_arr& a, size_t N);

// Input:
// Weights (stored in array w)
// Values (stored in array v)
// Number of distinct items (n)
// Knapsack capacity (W)
std::pair<int, int_arr> KnapSackUnbounded(int_arr& w, int_arr& v, int n, int W);

// Input:
// Weights (stored in array w)
// Values (stored in array v)
// Number of distinct items (n)
// Knapsack capacity (W)
int KnapSack(int_arr& w, int_arr& v, int n, int W);
