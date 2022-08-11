#include <assert.h>
#include <vector>
#include <array>
#include <functional>

using KeyTyp = unsigned short;
using ValueType = size_t;
using Typ = std::pair<KeyTyp, ValueType>;
using Array = std::vector<Typ>;
using IndexArray = std::vector<size_t>;
using GetKeyFn = std::function<const KeyTyp(const Typ&)>;

const size_t N = 1000000;

void PrepareData(Array& arr, size_t MAX)
{
	srand(1);
	// fill array
	for (size_t i = 0; i < arr.size(); i++)
	{
		arr[i] = {static_cast<KeyTyp>(MAX * rand() / RAND_MAX), i };
	}
}

bool CheckData(Array& InArr)
{
	bool res = true;
	for (size_t i = 1; i < InArr.size(); ++i)
	{
		if (InArr[i - 1].first > InArr[i].first
			|| (InArr[i - 1].first == InArr[i].first && InArr[i - 1].second > InArr[i].second)) {
			res = false;
			break;
		}
	}
	return res;
}

IndexArray CountKeysEqual(GetKeyFn GetKey, const Array& InArr, size_t MAX)
{
	IndexArray equals(MAX + 1);
	for (size_t i = 0; i < InArr.size(); ++i)
	{
		++equals[std::invoke(GetKey, InArr[i])];
	}
	return equals;
}

IndexArray CountKeyLess(IndexArray& equals, size_t MAX)
{
	IndexArray less(MAX + 1);
	for (size_t i = 1; i < equals.size(); ++i)
	{
		less[i] = less[i - 1] + equals[i - 1];
	}
	return less;
}

Array Rearrange(GetKeyFn GetKey, const Array& InArr, IndexArray& less)
{
	Array OutArr(InArr.size());
	auto& next = less;
	for (size_t i = 0; i < InArr.size(); ++i)
	{
		KeyTyp key = std::invoke(GetKey, InArr[i]);
		auto index = next[key];
		OutArr[index] = InArr[i];
		++next[key];
	}
	return OutArr;
}

Array CountingSort(GetKeyFn GetKey, const Array& InArr, size_t MAX)
{
	auto equals = CountKeysEqual(GetKey, InArr, MAX);
	auto less = CountKeyLess(equals, MAX);
	return Rearrange(GetKey, InArr, less);
}

Array RadixSort(const Array& InArr)
{
	GetKeyFn getKey1 = [](const Typ& elem) { return elem.first & 0xff; };
	auto pass1 = CountingSort(getKey1, InArr, 255);
	GetKeyFn getKey2 = [](const Typ& elem) { return (elem.first & 0xff00) >> 8; };
	auto pass2 = CountingSort(getKey2, pass1, 255);
	return pass2;
}

int main()
{
	Array A(N);
	size_t MAX = RAND_MAX;
	PrepareData(A, MAX);

	GetKeyFn getKey = [](const Typ& elem) { return elem.first; };
	
	auto ret1 = CountingSort(getKey, A, MAX);

	assert(CheckData(ret1));

	auto ret2 = RadixSort(A);

	assert(CheckData(ret2));


    return 0;
}

