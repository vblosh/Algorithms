/*
Задача на программирование: кодирование Хаффмана
По данной непустой строке ss длины не более 10^4
 , состоящей из строчных букв латинского алфавита, постройте оптимальный беспрефиксный код. В первой строке выведите количество различных букв kk, встречающихся в строке, и размер получившейся закодированной строки. В следующих kk строках запишите коды букв в формате "letter: code". В последней строке выведите закодированную строку.
Sample Input 1:

a

Sample Output 1:

1 1
a: 0
0

Sample Input 2:

abacabad

Sample Output 2:

4 14
a: 0
b: 10
c: 110
d: 111
01001100100111
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct CharFrequency 
{
    char ch;
    int frequency;
    CharFrequency* left, * right;

    CharFrequency(char ach,int afrequency) 
        :ch(ach), frequency(afrequency), left(nullptr), right(nullptr)
    {}
    CharFrequency(int afrequency, CharFrequency* aleft, CharFrequency *aright)
        :ch(0), frequency(afrequency), left(aleft), right(aright)
    {}

};

class MinCharFreqHeap
{
    vector<CharFrequency*> data;
public:
    MinCharFreqHeap(size_t size) {
        data.reserve(size);
    }
    CharFrequency* pop() {
       pop_heap(data.begin(), data.end()
           , [](auto lhs, auto rhs) { return lhs->frequency > rhs->frequency; });
       CharFrequency* ret = data.back();
       data.pop_back();
       return ret;
    }
    void push(CharFrequency* chf) {
        data.push_back(chf);
        push_heap(data.begin(), data.end()
            , [](auto lhs, auto rhs) { return lhs->frequency > rhs->frequency; });
    }
    bool empty() {
        return data.empty();
    }
};

class Huffman
{
public:
    static unordered_map<char, string>encode(const string& text)
    {
        // count frequencies
        unordered_map<char, int> char_frequencies;
        for (auto c : text) {
            char_frequencies[c]++;
        }
        size_t N = char_frequencies.size();
        // make heap
        MinCharFreqHeap heap(N);
        for (auto& chf : char_frequencies) {
            heap.push(new CharFrequency(chf.first, chf.second));
        }

        // shannon encoding
        for (size_t i = 0; i < N - 1; i++) {
            auto left = heap.pop();
            auto right = heap.pop();
            heap.push(new CharFrequency(left->frequency + right->frequency, left, right));
        }

        unordered_map<char, string> result;
        // get root of the btree
        result.reserve(N);
        auto root = heap.pop();
        if (N == 1) {
            result[root->ch] = "0";
        }
        else {
            DFS(root, "", result);
        }

        return result;
    }

private:
    static void DFS(CharFrequency* node, string path, unordered_map<char, string>& code)
    {
        if (node->ch != 0) {
            code[node->ch] = path;
            delete node;
            return;
        }

        DFS(node->left, path + '0', code);
        DFS(node->right, path + '1', code);
        delete node;
    }
};

int main() 
{
    string text;
    cin >> text;

    auto huffman_encoding = Huffman::encode(text);

    string encoded_text;
    for (auto c : text) {
        encoded_text += huffman_encoding[c];
    }

    cout << huffman_encoding.size() << " " << encoded_text.size() << endl;
    for (auto& encoded : huffman_encoding) {
        cout << encoded.first << ": " << encoded.second << endl;
    }
    cout << encoded_text << endl;

    return 0;
}