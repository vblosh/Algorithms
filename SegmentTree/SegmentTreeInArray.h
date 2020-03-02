#pragma once
#include <vector>
#include <functional>

// _A array element type, 
// _T segment tree element type, by default the same as array element type
template<class _A, class _T = _A>
class SegmentTreeInArray
{
public:
	// combine_func is used to combine to tree element together,
	// for instance for sum of array elements tree combine_func is [](int a, int b) { return a+b; },
	// for min of array elements tree combine_func is [](int a, int b) { return __min(a, b); }
	// for max of array elements tree combine_func is [](int a, int b) { return __max(a, b); }
	// 
	// assign_func is used to assign an array element to an tree element,
	// default implementation returns array element and can be used then 
	// tree element type is the same as array element type
	SegmentTreeInArray(std::function<_T(const _T&, const _T&)> combine_func
		, std::function<_T(const _A&)> assign_func = &SegmentTreeInArray::def_assign)
		: combine(combine_func), assign(assign_func)
	{
	}

	// build a segment tree from array
	void build(std::vector<_A>& arr)
	{
		size = arr.size();
		// что размер этого массива при такой нумерации надо ставить не 4n, а 2n. Дело в том, что
		// такая нумерация не идеально работает в случае, когда не является степенью двойки — тогда появляются
		//	пропущенные номера, которым не соответствуют никакие вершины дерева(фактически, нумерация ведёт себя
		//		подобно тому, как если бы округлили бы вверх до ближайшей степени двойки).Это не создаёт никаких сложностей
		//	при реализации, однако приводит к тому, что размер массива надо увеличивать до .
		tree.resize(4 * size);

		do_build(arr, 1, 0, size - 1);
	}

	// query tree element for array elements from left to rigth indexes inclusive
	_T query(size_t left, size_t right)
	{
		return do_query(1, 0, size - 1, left, right);
	}

	// update tree according new_value of array element in position
	void update(int position, _T new_value)
	{
		do_update(1, 0, size - 1, position, new_value);
	}

private:
	// left child index
	size_t left_child(size_t parent_idx)
	{
		return parent_idx * 2;
	}

	// right child index
	size_t right_child(size_t parent_idx)
	{
		return parent_idx * 2 + 1;
	}

	void do_build(vector<_A>& arr, size_t current, size_t left_idx, size_t right_idx)
	{
		if (left_idx == right_idx)
			tree[current] = assign(arr[left_idx]);
		else
		{
			size_t middle = (left_idx + right_idx) / 2;
			do_build(arr, left_child(current), left_idx, middle);
			do_build(arr, right_child(current), middle + 1, right_idx);
			tree[current] = combine(tree[left_child(current)], tree[right_child(current)]);
		}
	}

	_T do_query(size_t current, size_t left_idx, size_t right_idx, size_t left, size_t right)
	{
		if (left == left_idx && right == right_idx)
			return tree[current];
		size_t middle = (left_idx + right_idx) / 2;
		if (left <= __min(right, middle) && __max(left, middle + 1) <= right)
		{
			_T left_query = do_query(left_child(current), left_idx, middle, left, __min(right, middle));
			_T right_query = do_query(right_child(current), middle + 1, right_idx, __max(left, middle + 1), right);
			return combine(left_query, right_query);
		}
		else if(__max(left, middle + 1) <= right)
		{
			return do_query(right_child(current), middle + 1, right_idx, __max(left, middle + 1), right);
		}
		return do_query(left_child(current), left_idx, middle, left, __min(right, middle));
	}

	void do_update(int current, int left_idx, int right_idx, int pos, _T new_value)
	{
		if (left_idx == right_idx)
			tree[current] = new_value;
		else {
			int middle = (left_idx + right_idx) / 2;
			if (pos <= middle)
				do_update(left_child(current), left_idx, middle, pos, new_value);
			else
				do_update(right_child(current), middle + 1, right_idx, pos, new_value);
			tree[current] = combine(tree[left_child(current)], tree[right_child(current)]);
		}
	}

	static _T def_assign(const _A& arr_el)
	{
		return arr_el;
	}

	size_t size;
	std::vector<_T> tree;
	std::function<_T (const _T&, const _T&) > combine;
	std::function<_T(const _A&)> assign;
};
