// PrimaryCheck.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

bool CheckPrime(int x)
{
	if (x == 2)
		return true;

	if (x == 1 || ((x % 2) == 0))
		return false;

	int end = int(sqrt(x) + 0.5);

	for (int i = 3; i <= end; i=i+2)
	{
		if (x % i == 0)
			return false;
	}

	return true;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N;
	cin >> N;
	vector<int> arr(N);
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (CheckPrime(arr[i]))
			cout << "Prime\n";
		else
			cout << "Not prime\n";

	}

	return 0;
}
