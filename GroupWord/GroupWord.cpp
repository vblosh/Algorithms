/*
Sample Input["eat", "tea", "tan", "ate", "nat", "bat"]
Sample Output [["ate", "eat", "tea"], ["nat", "tan"], ["bat"]]

Т.е.сгруппировать слова по "общим буквам".#include <iostream>
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> input = { "eat", "tea", "tan", "ate", "nat", "bat" };
unordered_map<string, vector<string>> output;

int main()
{
    for (auto& word : input)
    {
        string sorted = word;
        sort(sorted.begin(), sorted.end());
        auto it = output.find(sorted);
        if (it != output.end())
            it->second.push_back(move(word));
        else
            output.insert({ sorted, {move(word)} });
    }

    cout << "[";

    for (auto it = output.begin(); it != output.end(); ++it)
    {
        cout << "[";
        for (auto& word : it->second)
        {
            cout << word << ",";
        }
        cout << "],";
    }
    cout << "]\n";
}
