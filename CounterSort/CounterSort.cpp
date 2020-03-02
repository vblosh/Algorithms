#include <vector>
typedef int Typ;
typedef std::vector<Typ> Array;

const int N = 8;
const int MAX = 10;

void PrepareData(Array& arr)
{
	srand(1);
	// fill array
	for (size_t i = 0; i < arr.size(); i++)
	{
		arr[i] = MAX * rand() / RAND_MAX + 1;
	}
}

void CounterSort(const Array& A, Array&As, int M)
{
	int n = A.size();
	std::vector<int> B(MAX);
	for (size_t i = 0; i < n; i++)
	{
		B[A[i]]++;
	}
	for (size_t i = 1; i < MAX; i++)
	{
		B[i] += B[i - 1];
	}

	for (int i = n-1; i >= 0; i--)
	{
		As[B[A[i]]-1] = A[i];
		B[A[i]]--;
	}
}


int main()
{

	Array A(N);
	PrepareData(A);
	
	Array As(N);
	CounterSort(A, As, MAX);

    return 0;
}

