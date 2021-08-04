#pragma once

using int_arr = std::vector<int>;

// Find Longest Increasing Subsequence
// Input:
// a input sequence
// N size of input sequence
// Returns: list of Longest Increasing Subsequences
std::vector<int_arr> MaxSubSequence(int_arr& a, size_t N);

// Solved unbounded KnapSack Problem
// Input:
// Weights (stored in array w)
// Values (stored in array v)
// Number of distinct items (n)
// Knapsack capacity (W)
// Returns: list of items in KnapSack
std::pair<int, int_arr> KnapSackUnbounded(int_arr& w, int_arr& v, int n, int W);

// Solved KnapSack Proble
// Input:
// Weights (stored in array w)
// Values (stored in array v)
// Number of distinct items (n)
// Knapsack capacity (W)
// Returns: max possible weight of items
int KnapSack(int_arr& w, int_arr& v, int n, int W);

// Find the longest common substring of two strings
// Input:
// str1 first string
// str2 second string
// Returns: the longest common substring of two strings
std::string MaxCommonSunstring(std::string str1, std::string str2);
