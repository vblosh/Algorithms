#pragma once
#include <assert.h>

typedef size_t vec_type;

class vector_bool
{
	vec_type * data;
	size_t size_;
public:
	vector_bool() : size_(0), data(nullptr)
	{
	}

	~vector_bool()
	{
		delete[] data;
	}

	void resize(size_t size)
	{
		assert(size > 0);
		size_ = size;
		size_t alloc_size = size / sizeof(vec_type) + 1;
		data = new vec_type[size / sizeof(vec_type) + 1];
		for (size_t i = 0; i < alloc_size; i++)
		{
			data[i] = 0;
		}
	}

	size_t size()
	{
		return size_;
	}

	bool at(size_t index)
	{
		assert(index < size_);
		return get_item(index) & get_bit(index);
	}

	void set(size_t index)
	{
		assert(index < size_);
		get_item(index) |= get_bit(index);
	}

	void clear(size_t index)
	{
		assert(index < size_);
		get_item(index) &= ~get_bit(index);
	}

private:
	vec_type get_bit(size_t index)
	{
		return 1 << (index % sizeof(vec_type));
	}

	vec_type& get_item(size_t index)
	{
		return data[index / sizeof(vec_type)];
	}
};
