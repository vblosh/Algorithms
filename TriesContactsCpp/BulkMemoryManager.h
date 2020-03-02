#pragma once
#include <stdint.h>
#include <forward_list>

template<size_t initSize, size_t alignment>
class bulk_memory_manager
{
public:
	typedef uint8_t* pointer;

	bulk_memory_manager() : increment(initSize), end(nullptr), block_end(nullptr) {}
	bulk_memory_manager(bulk_memory_manager const &) = delete;
	bulk_memory_manager& operator=(bulk_memory_manager const &) = delete;
	
	~bulk_memory_manager()
	{
		clear();
	}

	void* allocate(size_t n)
	{
		if (0 == n)
			return nullptr;

		size_t aligned_n = (n + alignment - 1) & ~alignment;
		pointer new_end = end + aligned_n;
		if (new_end > block_end)
		{
			while (increment < n)
			{
				increment *= 2;
			}
			do_allocate();
		}
		pointer res = end;
		end += n;
		return (res);
	}

	void deallocate(void* p, size_t n) {}

	void clear()
	{
		for (auto it : memory_blocks)
		{
			free(it);
		};
		memory_blocks.clear();
	}

private:
	pointer end;
	size_t increment;
	std::forward_list<pointer> memory_blocks;
	pointer block_end;

private:
	static size_t align_up(size_t n) noexcept
	{
		return (n + (alignment - 1)) & ~(alignment - 1);
	}

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
};

