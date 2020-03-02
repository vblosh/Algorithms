// TriesContactsCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "BulkAllocator.h"

using namespace std;

#define NUM_LETTER 26

using index_list = forward_list<size_t>;

struct TriesNode
{
	TriesNode(TriesNode* parent, int letterIndex) 
		: Parent(parent), LetterIndex(letterIndex)
	{
		for (size_t i = 0; i < NUM_LETTER; i++)
		{
			Children[i] = nullptr;
		}
	}

	TriesNode(const TriesNode&) = delete;

	~TriesNode()
	{
	}

	short int LetterIndex;
	index_list StringIndexes;
	TriesNode* Parent;
	TriesNode* Children[NUM_LETTER];
};

template <typename FancyPtr>
auto trueaddress(FancyPtr ptr)
{
	return !ptr ? nullptr : std::addressof(*ptr);
}

template<TriesNode*>
auto trueaddress(TriesNode* ptr)
{
	return ptr;
}

struct FindData
{
	FindData(index_list stringIndexes, short int endLetterIndex)
		: StringIndexes(stringIndexes), EndLetterIndex(endLetterIndex) {}

	short int EndLetterIndex;
	index_list StringIndexes;
};

using FindDataList = std::forward_list<FindData>;

template<class _Alloc = allocator<> >
class Tries
{
	using AllocTraits = std::allocator_traits<_Alloc>;

public:
	Tries(_Alloc& alloc = _Alloc()) 
		: allocator(alloc), letters(NUM_LETTER)
	{
		root = AllocTraits::allocate(allocator, 1);
		AllocTraits::construct(allocator, trueaddress(root), nullptr, 0);
	}

	~Tries()
	{
		Destroy(root);
	}

	void Add(const string& s)
	{
		size_t new_string_idx = strings.size();
		strings.push_back(s);

		TriesNode* node = root;
		size_t i = 0;
		DoFind(node, s, i);
		for (; i < s.size(); i++)
		{	
			AllocTraits::pointer new_node = AllocTraits::allocate(allocator, 1);
			AllocTraits::construct(allocator, trueaddress(new_node), node, node->LetterIndex + 1);
			(letters[Index(s[i])]).push_front(new_node);
			node->Children[Index(s[i])] = new_node;
			node = new_node;
		}
		while (node)
		{
			node->StringIndexes.push_front(new_string_idx);
			node = node->Parent;
		}
	}

	FindDataList Find(const string& s)
	{
		FindDataList result;

		for (TriesNode* node : letters[Index(s[0])])
		{
			size_t idx = 0;
			if (DoFind(node, s, idx))
			{
				result.push_front(FindData(node->StringIndexes, node->LetterIndex));
			}
		}
		return result;
	}

	const string& GetStrAtIndex(size_t index) const
	{
		return strings.at(index);
	}

private:
	TriesNode* root;
	_Alloc& allocator;
	vector<string> strings;
	vector< forward_list<TriesNode*> > letters;

	inline int Index(char ch)
	{
		return ch - 'a';
	}

	bool DoFind(TriesNode*& node, const string& str, size_t& i)
	{
		for (; i < str.size(); i++)
		{
			if (node->Children[Index(str[i])])
			{
				node = node->Children[Index(str[i])];
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	void Destroy(TriesNode* parent_node)
	{
		for (size_t i = 0; i < NUM_LETTER; i++)
		{
			TriesNode* node = parent_node->Children[i];
			if (node)
			{
				Destroy(node);
			}
		}
		AllocTraits::destroy(allocator, trueaddress(parent_node));
		AllocTraits::deallocate(allocator, parent_node, 1);
	}
};

enum Operation
{
	Add,
	Find,
};

struct OpData
{
	Operation op;
	string contact;
};

using my_mem_man = bulk_memory_manager<1024 * 1024, 4>;
using myalloc = bulk_allocator<TriesNode, my_mem_man>;

my_mem_man mem_manager;

template <class T, class _Arena>
_Arena& bulk_allocator<T, _Arena>::arena = mem_manager;

int main()
{
	{
		int N;
		cin >> N;
		vector<OpData> opData(N);
		size_t numFind = 0;

		string op, contact;
		for (int i = 0; i < N; i++)
		{
			cin >> op >> contact;
			if (op == "add")
			{
				opData[i].op = Operation::Add;
				opData[i].contact = contact;
			}
			else if (op == "find")
			{
				numFind++;
				opData[i].op = Operation::Find;
				opData[i].contact = contact;
			}
			else
			{
				cout << "Wrong operation!\n";
				break;
			}
		}

		vector<pair<string, FindDataList>> finds(numFind);

		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);

		LARGE_INTEGER start;
		QueryPerformanceCounter(&start);
		Tries<myalloc> tries;
		//		Tries<> tries;

		size_t idxFind = 0;
		for (OpData data : opData)
		{
			if (data.op == Operation::Add)
			{
				tries.Add(data.contact);
			}
			else
			{
				finds[idxFind++] = std::make_pair(data.contact, tries.Find(data.contact));
			}
		}

		LARGE_INTEGER end;
		QueryPerformanceCounter(&end);

		cout << "Total " << double(end.QuadPart - start.QuadPart)*1000.0 / freq.QuadPart << "ms\n";

		for (auto find : finds)
		{
			string& findstr = find.first;

			for (auto it = find.second.cbegin(); it != find.second.cend(); it++)
			{
				const FindData & fd = *it;
				for (size_t idx : fd.StringIndexes)
				{
					const string& str = tries.GetStrAtIndex(idx);
					string& substr = str.substr(fd.EndLetterIndex - findstr.size(), findstr.size());
					assert(substr == findstr);
				}
			}
		}
	}
    return 0;
}

