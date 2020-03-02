#pragma once
#include "BulkMemoryManager.h"

template <class T, class _Arena>
struct bulk_allocator {
	using value_type = T;
	using pointer = T *;

	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	bulk_allocator() noexcept {}
	template <class U, class A> bulk_allocator(const bulk_allocator<U, A>&) noexcept {}
	
	pointer allocate(size_t n)
	{
		return static_cast<pointer>(arena.allocate(n * sizeof(T)));
	}

	void deallocate(pointer p, size_t n) 
	{
		arena.deallocate(p, n * sizeof(T));
	}

	static _Arena& arena;
};

template <class T, class U, class A, class B>
constexpr bool operator== (const bulk_allocator<T, A>&, const bulk_allocator<U, B>&) noexcept
{
	return std::is_same<A, B>;
}

template <class T, class U, class A, class B>
constexpr bool operator!= (const bulk_allocator<T, A>& lhs, const bulk_allocator<U, A>& rhs) noexcept
{
	return !operator==(lhs, rhs);
}


