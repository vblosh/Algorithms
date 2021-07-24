#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <map>
#include <assert.h>
#include <algorithm>
#include "mask_cont.h"
#include "bitset.h"

using stringvec = std::vector<string>;
struct word_t
{
	stringvec wordlist;
	bvv::bitset disabled;
};

using word_cont = std::unordered_map<size_t, word_t*>;

bool sort_by_pos(const string_pos_t& lhs, const string_pos_t& rhs) { return rhs.initial_pos < lhs.initial_pos; }

class solver
{
	long backtracing_cnt = 0;
public:
	solver()
	{
	}

	~solver()
	{
		for (auto it : words)
		{
			delete it.second;
		}
	}

	void load_data(std::string filename)
	{
		auto fi = std::ifstream(filename);

		std::string strmasks;
		getline(fi, strmasks);
		std::string strwords;
		getline(fi, strwords);
		
		process_words(strwords);

		process_mask(strmasks);
		
		masks.sort();
	}

	void print_data()
	{
		std::cout << "masks table\n";
		std::cout << masks.size() << " masks found\n";

		std::cout << "words table\n";
		std::cout << "length\tsize\n";
		size_t total_words = 0;
		for (auto it : words)
		{
			total_words += it.second->wordlist.size();
			std::cout << it.first << '\t' << it.second->wordlist.size() << '\n';
		}
		std::cout << total_words << " total words\n";
		assert(masks.size() == total_words);
	}

	bool solve()
	{
		return backtracking(masks.begin());
	}

	void print_solution()
	{
		std::cout << "solution requires " << backtracing_cnt << " recursive calls\n";
		//std::sort(solution.begin(), solution.end(), sort_by_pos);
		//for (auto it = solution.rbegin(); it != solution.rend(); ++it)
		//{
		//	std::cout << it->str << " ";
		//}
	}
private:

	void process_mask(std::string& inputstr) {
		std::regex word_regex("[A-Za-z_]+");
		std::regex_token_iterator<std::string::iterator> matches(inputstr.begin(), inputstr.end(), word_regex);
		size_t init_pos = 0;
		while (matches != std::regex_token_iterator<std::string::iterator>())
		{
			std::string mask = *matches++;
			masks.push_back(mask, init_pos++);
		}
	}

	void process_words(std::string& inputstr) {
		std::regex word_regex(" ");
		std::regex_token_iterator<std::string::iterator> matches(inputstr.begin(), inputstr.end(), word_regex, -1);

		while (matches != std::regex_token_iterator<std::string::iterator>())
		{
			std::string word = *matches++;
			if (words.find(word.size()) == words.end())
			{
				words[word.size()] = new word_t();
			}
			words[word.size()]->wordlist.push_back(word);
		}

		for (auto it : words)
		{
			word_t* pword = it.second;
			pword->disabled.resize(pword->wordlist.size());
		}
	}

	bool compare(mask& mask, string& word)
	{
		if (word.size() != mask.size())
			return false;

		auto word_it = word.cbegin();
		for (auto letter : mask) {
			if (!(letter == '_' || letter == *word_it))
				return false;
			++word_it;
		}
		return true;
	}

	bool backtracking(mask_cont::iterator mit)
	{
		++backtracing_cnt;

		if (mit == masks.end())
			return true;

		auto next_mit = mit;
		++next_mit;
		string& strmask = mit->str;

		auto it = words.find(strmask.size());
		if (it == words.end())
			return false;

		word_t* word = it->second;
		size_t i = word->disabled.find1zero(0);
		for (; i < word->disabled.size(); i = word->disabled.find1zero(i))
		{
			if (compare(strmask, word->wordlist[i]))
			{
				// remove candidate from solution
				word->disabled.set(i);
				if (backtracking(next_mit))
				{
					solution.push_back(string_pos_t(word->wordlist[i], mit->initial_pos));
					return true;
				}
				// solution is not successfull, restore candidate
				word->disabled.reset(i);
			}
		}
		return false;
	}

private:
	mask_cont masks;
	word_cont words;
	std::vector < string_pos_t > solution;
};
