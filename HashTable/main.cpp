// HashTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <unordered_map>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

const int N = 10000;
int set1[N], set2[N];

const size_t WARM_UP_TIMES = 5;
const size_t LOOPS = 10;


void prepare_data()
{
	ifstream f1("set1.txt");
	for (size_t i = 0; i < N; i++)
	{
		f1 >> set1[i];
	}
	ifstream f2("set2.txt");
	for (size_t i = 0; i < N; i++)
	{
		f2 >> set2[i];
	}

	/*
	srand(1234567);
	for (int i = 0; i < N; i++)
	{
		set1[i] = rand();
	}

	srand(7654321);
	for (int i = 0; i < N; i++)
	{
		set2[i] = rand();
	}
	*/
}

int count_intersections()
{
	hash_table<int, int, int, int>  hashTable = hash_table<int, int, int, int>(N);
	for (int i = 0; i < N; i++)
	{
		hashTable.get(set1[i], i);
	}

	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (hashTable.contains(set2[i]))
			cnt++;
	}
	return cnt;
}

void prepare_data1(int range_min, int range_max)
{
	srand(1234567);
	for (int i = 0; i < N; i++)
	{
		set1[i] = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)	+ range_min + 0.5;
	}
}

struct key_hasher
{
	std::size_t operator()(const int& k) const
	{
		return k;
	}
};

void perf_test()
{
	hash_table<int, int, int, int&, key_hasher> table(N);
	for (int i = 0; i < N; i++)
	{
		table[i]++;
	}
}

void perf_test_std()
{
	std::unordered_map<int, int, key_hasher> std_table(N);
	for (int i = 0; i < N; i++)
	{
		std_table[i]++;
	}
}

void test_hash_table()
{
	hash_table<int, int, int, int&, key_hasher> table(N);
	for (int i = 0; i < N; i++)
	{
		table[set1[i]]++;
	}

	std::unordered_map<int, int, key_hasher> std_table(N);
	for (int i = 0; i < N; i++)
	{
		std_table[set1[i]]++;
	}

	assert(table.size() == std_table.size());
	for (auto it : table)
	{
		assert(std_table[it.key] == it.value);
	}
}

UINT64 inline GetRDTSC(void) {
	__asm {
		; Flush the pipeline
		XOR eax, eax
		CPUID
		; Get RDTSC counter in edx : eax
		RDTSC
	}
}

UINT64 inline GetRDTSCP(void) {
	__asm {
		; Get RDTSC counter in edx : eax
		RDTSCP
	}
}

int main()
{
	UINT64 start, total;
	std::vector<UINT64> times(LOOPS);
//	prepare_data1(0, RAND_MAX);

	test_hash_table();

	// warm-up
	for (size_t i = 0; i < WARM_UP_TIMES; i++)
	{
		perf_test();
	}

	for (size_t i = 0; i < LOOPS; i++)
	{
		start = GetRDTSC();
		perf_test();
		times[i] = GetRDTSC() - start;
	}
	for (auto tim : times)
		cout << "HashTable perfomance " << tim << " ticks" << endl;

	// warm-up
	for (size_t i = 0; i < WARM_UP_TIMES; i++)
	{
		perf_test_std();
	}

	for (size_t i = 0; i < LOOPS; i++)
	{
		start = GetRDTSC();
		perf_test_std();
		times[i] = GetRDTSC() - start;
	}
	for(auto tim : times)
		cout << "std::unordered_map perfomance " << tim << " ticks" << endl;
	
	/*

	prepare_data();

	int n = count_intersections();

	cout << "HashTable Intersect = " << n << ", Elapsed " << end.QuadPart - start.QuadPart << " ticks" << endl;



	hash_table<int, int, int, int&, key_hasher> table(10);
	table[1] = 1;
	table[2] = 2;
	bool found = table.contains(1);
	table.remove(1);
	found = table.contains(1);
	table.get(3, 3);
	int val = table[3];
	table[3]++;

	cout << "table size=" << table.size() << endl;
	for (auto i = table.begin(); i != table.end(); ++i)
	{
		cout << "table[" << (*i).key << "]=" << (*i).value << endl;
	}

	cout << "table size=" << table.size() << endl;
	for (auto it : table)
	{
		cout << "table[" << it.key << "]=" << it.value << endl;
	}
	
	auto beg = table.begin();
	*/
    return 0;

}

