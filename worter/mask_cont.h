#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <map>
#include <assert.h>
#include <algorithm>

using std::string;
using mask = std::string;

struct string_pos_t
{
	string_pos_t(string astr, size_t ainitial_pos) : str(astr), initial_pos(ainitial_pos) {}
	string str;
	size_t initial_pos;
};

struct size_freq_t
{
	size_freq_t(size_t size1, size_t freq1) : size(size1), freq(freq1) {}

	size_t size;
	size_t freq;
};

class mask_cont
{
	using mask_vec = std::vector<string_pos_t>;

	std::unordered_map<size_t, mask_vec*> _data;
	std::vector<size_freq_t> _sort_order;
	size_t _size;

public:
	mask_cont() : _size(0) {}
	~mask_cont()
	{
		for (auto it : _data)
		{
			delete it.second;
		}
	}

	class mask_cont_iterator
	{
		mask_cont& _parent;
		size_t _cur_bucket;
		mask_vec::iterator _cur_mask;

		mask_vec* get_stringvec(size_t cur_bucket)
		{
			size_t mask_size = _parent._sort_order[cur_bucket].size;
			return _parent._data[mask_size];
		}

		void advance()
		{
			++_cur_mask;
			if (_cur_mask == get_stringvec(_cur_bucket)->end())
			{
				++_cur_bucket;
				if (_cur_bucket < _parent._sort_order.size())
					_cur_mask = get_stringvec(_cur_bucket)->begin();
			}
		}
	public:
		typedef ptrdiff_t difference_type; //almost always ptrdiff_t
		typedef string_pos_t value_type; //almost always T
		typedef string_pos_t& reference; //almost always T& or const T&
		typedef string_pos_t* pointer; //almost always T* or const T*
		typedef std::forward_iterator_tag iterator_category; //usually std::forward_iterator_tag 

		mask_cont_iterator(mask_cont& parent) : _parent(parent), _cur_bucket(0)
		{
			_cur_mask = get_stringvec(_cur_bucket)->begin();
		}

		mask_cont_iterator(mask_cont& parent, size_t cur_bucket, mask_vec::iterator cur_mask)
			: _parent(parent), _cur_bucket(cur_bucket), _cur_mask(cur_mask)
		{
		}

		~mask_cont_iterator() {}

		mask_cont_iterator  operator++(int) /* postfix */
		{
			mask_cont_iterator ret = *this;
			advance();
			return ret;
		}

		mask_cont_iterator& operator++()    /* prefix */
		{
			advance();
			return *this;
		}

		reference operator* () const 
		{ 
			return *_cur_mask; 
		}

		pointer   operator->() const 
		{ 
			return _cur_mask.operator->(); 
		}

		//iterator  operator+ (difference_type v)   const { return pos_ + v; }
		bool      operator==(const mask_cont_iterator& rhs) const
		{
			return _cur_bucket == rhs._cur_bucket && _cur_mask == rhs._cur_mask;
		}
		bool      operator!=(const mask_cont_iterator& rhs) const
		{
			return !operator==(rhs);
		}
	};

	typedef mask_cont_iterator iterator;

	void push_back(string mask, size_t initial_pos)
	{
		if (_data.find(mask.size()) == _data.end())
		{
			_data[mask.size()] = new std::vector<string_pos_t>();
		}
		_data[mask.size()]->push_back(string_pos_t(mask, initial_pos));
		++_size;
	}

	mask_cont::iterator begin()
	{
		return mask_cont_iterator(*this);
	}

	mask_cont::iterator end()
	{
		return mask_cont_iterator(*this, _sort_order.size(), get_stringvec(_sort_order.size() - 1)->end());
	}

	void sort()
	{
		_sort_order.clear();
		for (auto it : _data)
		{
			_sort_order.push_back(size_freq_t{ it.first, it.second->size() });
		}
		std::sort(_sort_order.begin(), _sort_order.end(), [](auto& lhs, auto& rhs) { return lhs.freq < rhs.freq; });
	}

	size_t size()
	{
		return _size;
	}
private:
	mask_vec* get_stringvec(size_t cur_bucket)
	{
		size_t mask_size = _sort_order[cur_bucket].size;
		return _data[mask_size];
	}

};
