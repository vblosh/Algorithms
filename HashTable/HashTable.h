#pragma once
#include "Hasher.h"
#include "vector_bool.h"

template<class key_type, // key type
	class value_type, // mapped type
	class key_ref = key_type&, // key type reference
	class value_ref = value_type&, // mapped type reference
	class hasher = Meiyan_hasher<key_type> // hash functor
	>
class hash_table
{
	const double FILL_FACTOR = 0.7;
	vector_bool used;
	key_type* keys;
	value_type* items;
	size_t capacity;
	size_t probing_seed;
	hasher hash_function;
	size_t size_;
	size_t probing_count;

public:
	typedef hash_table<key_type, value_type, key_ref, value_ref, hasher> hash_table_type;
	
	struct iterator_item
	{
		const key_ref key;
		value_ref value;
	};

	template<bool is_const_iterator = true>
	class const_noconst_iterator : public std::iterator<std::forward_iterator_tag, key_ref>
	{
		typedef typename std::conditional<is_const_iterator, const hash_table_type*, hash_table_type*>::type parent_pointer_type;

		parent_pointer_type parent;
		size_t pos;
	
	public:
		const_noconst_iterator(hash_table_type* aparent, size_t x) : parent(aparent), pos(x)
		{
			skip_unused();
		}

		const_noconst_iterator(const const_noconst_iterator<false>& other) : parent(other.parent), pos(other.pos) 
		{
		}

		const_noconst_iterator& operator++()
		{
			++pos;
			skip_unused();
			return *this;
		}

		const_noconst_iterator operator++(int)
		{
			iterator tmp(*this);
			operator++();
			return tmp;
		}

		bool operator==(const const_noconst_iterator& rhs) const { return parent = rhs.parent && pos == rhs.pos; }
		bool operator!=(const const_noconst_iterator& rhs) const { return parent = rhs.parent && pos != rhs.pos; }
		
		iterator_item operator*() 
		{
			return iterator_item{ parent->keys[pos], parent->items[pos] };
		}

		void skip_unused()
		{
			while (pos != parent->capacity && !parent->used.at(pos)) ++pos;
		}
	};

	typedef const_noconst_iterator<false> iterator;
	typedef const_noconst_iterator<true> const_iterator;

	hash_table(size_t acapacity) : 
		capacity(acapacity / FILL_FACTOR + 0.5),  size_(0), probing_count(0)
	{
		used.resize(capacity);
		keys = new key_type[capacity];
		items = new value_type[capacity];
	}

	~hash_table()
	{
		delete[] keys;
		delete[] items;
	}

	iterator begin()
	{
		return iterator(this, 0);
	}

	iterator end()
	{
		return iterator(this, capacity);
	}

	const_iterator cbegin()
	{
		return const_iterator(this, 0);
	}

	const_iterator cend()
	{
		return const_iterator(this, capacity);
	}

	size_t size() const
	{
		return size_;
	}

	bool remove(key_ref key)
	{
		auto found_res = find_key(key);
		bool found = found_res.first;
		if (found)
		{
			auto pos = found_res.second;
			used.clear(pos);
			--size_;
		}
		return found;
	}

	bool contains(key_ref key)
	{
		auto findRes = find_key(key);
		return findRes.first;
	}

	value_ref get(key_ref key, value_type item = value_type())
	{
		auto found_res = find_key(key);
		bool found = found_res.first;
		auto pos = found_res.second;
		if (!found)
		{
			used.set(pos);
			++size_;
			keys[pos] = key;
			items[pos] = item;
		}
		return items[pos];
	}

	value_ref operator[](key_ref key)
	{
		return get(key);
	}

private:
	/// <summary>
	/// Quadratic probing
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	size_t probing(size_t pos)
	{
		probing_seed++;
		return (pos + probing_seed * probing_seed) % capacity;
	}

	void init_probing()
	{
		probing_seed = 0;
	}

	std::pair<bool, size_t> find_key(key_ref item)
	{
		size_t pos = hash_function(item) % capacity;
		init_probing();
		while (used.at(pos) && keys[pos] != (item))
		{
			pos = probing(pos);
		}
#ifdef _DEBUG
		probing_count += probing_seed;
#endif // DEBUG

		bool found = used.at(pos) && keys[pos] == (item);
		return std::make_pair(found, pos);
	}
};
