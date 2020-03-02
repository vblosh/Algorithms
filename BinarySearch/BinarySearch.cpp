#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int BinarySearch(const int* data, int l, int r, int val)
{
	if (l > r)
		return -1;

	int m = (l + r) / 2;
	
	if (data[m] < val)
		return BinarySearch(data, m + 1, r, val);
	else if(data[m] > val)
		return BinarySearch(data, l, m - 1, val);
	else
		return (m + 1);
}

int binary_search(const int* a, int low, int high, int target) {
	if (high < low)
		return -1;
	int middle = (low + high) / 2;
	if (target < a[middle])
		return binary_search(a, low, middle - 1, target);
	else if (target > a[middle])
		return binary_search(a, middle + 1, high, target);
	else 
		return middle + 1;
}
int get_pos(const std::vector<int> &numbers, int number) 
{
	//return binary_search(&numbers[0], 0, numbers.size() - 1, number);
	return BinarySearch(&numbers[0], 0, numbers.size()-1, number);
}

int main(void) {
	int number_count;
	std::cin >> number_count;
	std::vector<int> numbers(number_count);
	for (auto &number : numbers) {
		std::cin >> number;
	}
	assert(std::is_sorted(numbers.begin(), numbers.end()));

	int query_count;
	std::cin >> query_count;
	while (query_count-- > 0) {
		int number;
		std::cin >> number;
		std::cout << get_pos(numbers, number) << " ";
	}
	std::cout << std::endl;
}