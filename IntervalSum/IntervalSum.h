#pragma once

void find_intervals(std::vector<int>& cumulative_sum, std::vector<int>& input, std::unordered_map<int, std::set<int>>& seek_sums, int target);
