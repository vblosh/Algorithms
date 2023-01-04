/*
Задача на программирование: декодирование Хаффмана

Восстановите строку по её коду и беспрефиксному коду символов.

В первой строке входного файла заданы два целых числа kk и ll через пробел — количество различных букв, 
встречающихся в строке, и размер получившейся закодированной строки, соответственно. 
В следующих kk строках записаны коды букв в формате "letter: code". 
Ни один код не является префиксом другого. Буквы могут быть перечислены в любом порядке. 
В качестве букв могут встречаться лишь строчные буквы латинского алфавита; 
каждая из этих букв встречается в строке хотя бы один раз. 
Наконец, в последней строке записана закодированная строка. 
Исходная строка и коды всех букв непусты. 
Заданный код таков, что закодированная строка имеет минимальный возможный размер.

В первой строке выходного файла выведите строку ss. Она должна состоять из строчных букв латинского алфавита. 
Гарантируется, что длина правильного ответа не превосходит 10^4
  символов.

Sample Input 1:

1 1
a: 0
0
Sample Output 1:

a
Sample Input 2:

4 14
a: 0
b: 10
c: 110
d: 111
01001100100111
Sample Output 2:

abacabad

*/

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    int num_ch, len;
    cin >> num_ch >> len;
    unordered_map<string, char> huffman_encode;
    char ch, delimiter;
    string code;

    for (size_t i = 0; i < num_ch; i++)
    {
        cin >> ch >> delimiter;
        cin >> code;
        huffman_encode[code] = ch;
    }
    string encoded_text;
    cin >> encoded_text;

    int idx = 0;
    string current;
    while (idx < encoded_text.size())
    {
        current += encoded_text[idx++];
        auto it = huffman_encode.find(current);
        if (it != huffman_encode.end()) {
            cout << it->second;
            current.clear();
        }
    }
}

