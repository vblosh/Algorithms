
/*
Дан список интов, повторяющихся элементов в списке нет.Нужно преобразовать это множество в строку, сворачивая соседние по числовому ряду числа в диапазоны.Примеры:
[1, 4, 5, 2, 3, 9, 8, 11, 0] = > "0-5,8-9,11"
[1, 4, 3, 2] = > "1-4"
[1, 4] = > "1,4"
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> data1 = { 1, 4, 5, 2, 3, 9, 8, 11, 0 };
vector<int> data2 = { 1, 4, 3, 2 };
vector<int> data3 = { 1, 4 };

void print_data(vector<int>& data)
{
    cout << '[';
    for (auto& el : data)
    {
        cout << el << ", ";
    }
    cout << "]=";
}

void print_range(int start, int end)
{
    if (start == end)
        cout << start;
    else {
        cout << start << '-' << end;
    }
    cout << ',';
}

void solve_ranges(vector<int>& data)
{
    print_data(data);
    sort(data.begin(), data.end());

    int start = data[0];
    int prev = start;

    for (auto it = data.begin() + 1; it != data.end(); ++it)
    {
        int next = *it;
        if(next == prev + 1)
        {
            prev = next;
        }
        else
        {
            print_range(start, prev);
            start = next;
            prev = start;
        }
    }
    print_range(start, prev);
    cout << endl;
}

int main()
{
    solve_ranges(data1);
    solve_ranges(data2);
    solve_ranges(data3);
}
