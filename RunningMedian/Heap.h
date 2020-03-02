#pragma once
#include <vector>

template<class _T, typename _Pr>
class heap
{
	std::vector<_T> _data;
	_Pr comp;
public:

	bool empty() const
	{
		return _data.empty();
	}

	size_t size() const
	{
		return _data.size();
	}

	_T& top()
	{
		return _data[0];
	}

	template<typename T>
	void add(T&& val)
	{
		_data.push_back(std::forward<T>(val));
		heapfy_up();
	}

	void remove_top()
	{
		remove_at(0);
	}

	void remove_at(size_t idx)
	{
		_data[idx] = _data[_data.size() - 1];
		_data.pop_back();
		heapfy_down(idx);
	}

	void remove(_T& val)
	{
		auto it = std::find(_data.begin(), _data.end(), std::forward<_T>(val));
		if (it != _data.end())
		{
			remove_at(it - _data.begin());
		}
	}

private:
	size_t parent(size_t idx)
	{
		return (idx - 1) / 2;
	}

	size_t left(size_t idx)
	{
		return idx * 2 + 1;
	}

	size_t right(size_t idx)
	{
		return idx * 2 + 2;
	}

	void heapfy_down(size_t idx)
	{
		size_t new_idx;
		for (;;)
		{
			if (left(idx) < _data.size() && right(idx) < _data.size())
			{
				new_idx = !comp(_data[left(idx)], _data[right(idx)]) ? left(idx) : right(idx);
			}
			else if (left(idx) < _data.size())
			{
				new_idx = left(idx);
			}
			else
			{
				break;
			}

			if (comp(_data[idx], _data[new_idx]))
			{
				std::swap(_data[idx], _data[new_idx]);
				idx = new_idx;
			}
			else
			{
				break;
			}
		}
	}

	void heapfy_up()
	{
		size_t idx = _data.size() - 1;
		while (idx > 0 && !comp(_data[idx], _data[parent(idx)]))
		{
			std::swap(_data[idx], _data[parent(idx)]);
			idx = parent(idx);
		}
	}
};
