#pragma once
#include <string>

unsigned int Hash_Meiyan(const char *str, size_t wrdlen)
{
	const unsigned int PRIME = 709607;
	unsigned int hash32 = 2166136261;
	const char *p = str;

	for (; wrdlen >= 2 * sizeof(unsigned int); wrdlen -= 2 * sizeof(unsigned int), p += 2 * sizeof(unsigned int)) {
		hash32 = (hash32 ^ (*(unsigned int *)p << 5 ^ *(unsigned int *)(p + 4))) * PRIME;
	}
	// Cases: 0,1,2,3,4,5,6,7
	if (wrdlen & sizeof(unsigned int)) {
		hash32 = (hash32 ^ *(unsigned short*)p) * PRIME;
		p += sizeof(unsigned short);
		hash32 = (hash32 ^ *(unsigned short*)p) * PRIME;
		p += sizeof(unsigned short);
	}
	if (wrdlen & sizeof(unsigned short)) {
		hash32 = (hash32 ^ *(unsigned short*)p) * PRIME;
		p += sizeof(unsigned short);
	}
	if (wrdlen & 1)
		hash32 = (hash32 ^ *p) * PRIME;

	return hash32 ^ (hash32 >> 16);
}

template<class _T>
struct Meiyan_hasher
{	
	size_t operator()(const _T& _Keyval) const
	{	
		return (Hash_Meiyan((const char *)&_Keyval, sizeof(_T)));
	}
};

template<>
struct Meiyan_hasher<std::string>
{
	size_t operator()(const std::string& _str) const
	{
		return (Hash_Meiyan(_str.c_str(), _str.size()));
	}
};
