#pragma once
#include <vector>
#include <functional>

template<class _T>
class SegmentTreeInArray2D
{
public:
	SegmentTreeInArray2D(std::function<_T(_T, _T)> combine_func)
		: combine(combine_func)
	{
	}

	void build(std::vector<std::vector<_T>>& arr)
	{
		size1 = arr.size();
		size2 = arr[0].size2();
		// что размер этого массива при такой нумерации надо ставить не 4n, а 2n. Дело в том, что
		// такая нумерация не идеально работает в случае, когда не является степенью двойки — тогда появляются
		//	пропущенные номера, которым не соответствуют никакие вершины дерева(фактически, нумерация ведёт себя
		//		подобно тому, как если бы округлили бы вверх до ближайшей степени двойки).Это не создаёт никаких сложностей
		//	при реализации, однако приводит к тому, что размер массива надо увеличивать до .
		tree.resize(4 * size1);

		do_build(arr, 1, 0, size1 - 1);
	}

	_T query(size_t left, size_t right)
	{
		return do_query(1, 0, size1 - 1, left, right);
	}

	void update(int pos, _T new_value)
	{
		do_update(1, 0, size1 - 1, pos, new_value);
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

	void do_build(vector<_T>& arr, size_t current, size_t left_idx, size_t right_idx)
	{
		if (left_idx == right_idx)
			tree[current] = arr[left_idx];
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
		else if (__max(left, middle + 1) <= right)
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

	std::vector<_T> tree;
	size_t size1;
	size_t size2;
	std::function<_T(_T, _T) > combine;
};
