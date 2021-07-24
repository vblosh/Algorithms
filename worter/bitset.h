#pragma once
#include <stdint.h>
#include <bit>

#define WORD_LEN 64

namespace bvv
{
	class bitset
	{
	public:
		bitset() : _data(nullptr), _size(0)
		{
		}

		~bitset()
		{
			delete[] _data;
		}

		void resize(size_t size)
		{
			delete[] _data;
			_size = size;
			size_t numwords = size / WORD_LEN + 1;
			_data = new uint64_t[numwords];
			for (size_t i = 0; i < numwords; i++)
			{
				_data[i] = 0l;
			}
			set(_size);
		}

		size_t size()
		{
			return _size;
		}

		void set(size_t pos)
		{
			uint64_t& word = _data[pos / WORD_LEN];
			word |= (uint64_t)0b1 << (pos % WORD_LEN);
		}

		void reset(size_t pos)
		{
			uint64_t& word = _data[pos / WORD_LEN];
			word &= ~((uint64_t)0b1 << (pos % WORD_LEN));
		}

		size_t find1one(size_t start_pos)
		{
			size_t word_pos = start_pos / WORD_LEN;
			auto bitpos = start_pos % WORD_LEN;
			uint64_t msk = ((uint64_t)0xffffffffffffffff << start_pos);
			if ((_data[word_pos] & msk) == 0x0)
			{
				while (_data[++word_pos] == 0x0);
				bitpos = std::countr_zero(_data[word_pos]);
			}
			else
				bitpos = std::countr_zero(_data[word_pos] & msk);

			return word_pos * WORD_LEN + bitpos;
		}

		size_t find1zero(size_t start_pos)
		{
			size_t word_pos = start_pos / WORD_LEN;
			auto bitpos = start_pos % WORD_LEN;
			uint64_t msk = ~((uint64_t)0xffffffffffffffff << start_pos); 
			if ((_data[word_pos] | msk) == 0xffffffffffffffff)
			{
				while (_data[++word_pos] == 0xffffffffffffffff);
				bitpos = std::countr_one(_data[word_pos]);
			}
			else
				bitpos  = std::countr_one(_data[word_pos] | msk);

			return word_pos * WORD_LEN + bitpos;
	}

	private:
		uint64_t* _data;
		size_t _size;
	};

}