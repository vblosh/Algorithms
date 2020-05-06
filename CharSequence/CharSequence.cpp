// CharSequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Есть строка. Выведите максимальную длину подряд идущих символов для всех символов.
Т.е. для aabccaaab, нужно выдать a: 3, b:1, c:2
*/
#include <iostream>
#include <string>
#include <unordered_map>

std::string input = "aabccaaab";
std::unordered_map<char, int> sequenceLength;

int main()
{
    char curChar = input[0];
    int curLength = 1;

    for (char ch : input.substr(1))
    {
        if (ch == curChar)
        {
            curLength++;
        }
        else
        {
            if (sequenceLength[curChar] < curLength)
            {
                sequenceLength[curChar] = curLength;
            }
            curChar = ch;
            curLength = 1;
        }
    }

    for (auto seqLen : sequenceLength)
    {
        std::cout << seqLen.first << ':' << seqLen.second << ", ";
    }
}
