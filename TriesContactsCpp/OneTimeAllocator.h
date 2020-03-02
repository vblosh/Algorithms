pragma once

#include <stdlib.h> //size_t, malloc, free
#include <new> // bad_alloc, bad_array_new_length
#include <memory>
#include <forward_list>

template<typename T, std::size_t initSize = 16>
class OneTimeAllocPolicy 
{
public:
	//    typedefs
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

public:
	//    convert an OneTimeAllocPolicy<T> to OneTimeAllocPolicy<U>
	template<typename U>
	struct rebind {
		typedef OneTimeAllocPolicy<U, numBlocks> other;
	};

public:
	inline explicit OneTimeAllocPolicy() : increment(initSize), end(nullptr), block_end(nullptr) {}
	inline explicit OneTimeAllocPolicy(OneTimeAllocPolicy const&) : OneTimeAllocPolicy() {}
	template <typename T2, std::size_t N2>
	inline explicit	OneTimeAllocPolicy(OneTimeAllocPolicy<T2, N2> const&) : OneTimeAllocPolicy() {}
	
	inline ~OneTimeAllocPolicy() 
	{
		for (auto it : memory_blocks)
		{
			free(it);
		};
	}

	//    memory allocation
	inline pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0) 
	{
		if (0 == cnt)
			return nullptr;

		pointer new_end = end + cnt * sizeof(T);
		if (new_end > block_end)
		{
			while (increment < cnt)
			{
				increment *= 2;
			}
			do_allocate();
		}
		pointer res = end;
		end += num_bytes;
		return res;
	}

	inline void deallocate(pointer p, size_type cnt) {	}

	//    size
	inline size_type max_size() const {
		return std::numeric_limits<size_type>::max() / sizeof(T);
	}

private:
	pointer end;
	size_type increment;
	std::forward_list<pointer> memory_blocks;
	pointer block_end;

private:
	void do_allocate()
	{
		pointer mem_block = (pointer)malloc(increment);
		if (!mem_block)
			throw std::bad_alloc();
		memory_blocks.push_front(mem_block);
		end = mem_block;
		block_end = mem_block + increment;
		increment *= 2;
	}
};    //    end of class OneTimeAllocPolicy


//    determines if memory from another allocator
//    can be deallocated from this one
template<typename T, std::size_t N>
inline bool operator==(OneTimeAllocPolicy<T, N> const&,
	OneTimeAllocPolicy<T, N> const&) {
	return true;
}
template<typename T, std::size_t N, typename T2, std::size_t N2>
inline bool operator==(OneTimeAllocPolicy<T,
	N> const&, OneTimeAllocPolicy<T2, N2> const&) {
	return false;
}
template<typename T, std::size_t N, typename OtherAllocator>
inline bool operator==(OneTimeAllocPolicy<T,
	N> const&, OtherAllocator const&) {
	return false;
}

