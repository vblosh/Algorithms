#include <iostream>
#include <assert.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include "SegmentTree.h"
#include "SegmentTreeInArray.h"

typedef int _T;
using intvec = std::vector<int>;
intvec Combine(intvec a, intvec b)
{
	intvec res(a.size() + b.size());
	std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
	return res;
}

int main()
{
	int N;
	cin >> N;
	vector<_T> arr(N);
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}

	int Q;
	cin >> Q;
	vector<int> left(Q), right(Q);
	for (int i = 0; i < Q; i++)
	{
		cin >> left[i] >> right[i];
	}

	{
		SegmentTreeInArray < int > sumTree([](int a, int b) { return a + b; });
		sumTree.build(arr);

		_T new_val = 11;
		size_t pos = 2;
		arr[pos] = new_val;
		sumTree.update(pos, new_val);

		for (int i = 0; i < Q; i++)
		{
			assert(left[i] < arr.size() && right[i] < arr.size());
			_T q = sumTree.query(left[i], right[i]);
			_T sum = 0;
			for (size_t j = left[i]; j <= right[i]; j++)
			{
				sum += arr[j];
			}
			assert(q == sum);
			cout << q << endl;
		}
	}
	
	{
		SegmentTreeInArray < int > minTree([](int a, int b) { return __min(a, b); });
		minTree.build(arr);

		_T new_val = 0;
		size_t pos = 2;
		arr[pos] = new_val;
		minTree.update(pos, new_val);

		for (int i = 0; i < Q; i++)
		{
			assert(left[i] < arr.size() && right[i] < arr.size());
			_T q = minTree.query(left[i], right[i]);
			_T __min = INT_MAX;
			for (size_t j = left[i]; j <= right[i]; j++)
			{
				if (arr[j] < __min)
					__min = arr[j];
			}
			assert(q == __min);
			cout << q << endl;
		}
	}

	{
		auto combine = [](const intvec& a, const intvec& b)
		{
			intvec res;
			res.reserve(a.size() + b.size());
			std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
			return res;
		};
		auto assign = [](const int& a) { 
			intvec ret(1);
			ret[0] = a;
			return ret;
		};
		SegmentTreeInArray < int, intvec > sortTree(combine, assign);
		sortTree.build(arr);

		for (int i = 0; i < Q; i++)
		{
			assert(left[i] < arr.size() && right[i] < arr.size());
			auto q = sortTree.query(left[i], right[i]);
			for (int j = 0; j < q.size() - 1; j++)
			{
				assert(q[j] <= q[j + 1]);
			}
		}
	}

	return 0;
}

