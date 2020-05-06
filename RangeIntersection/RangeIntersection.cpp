// RangeIntersection calculate intersection of all ranges in rangesList

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


using RangeT = int;
using Range = std::pair<RangeT, RangeT>; // [start, end)
using Ranges = std::vector<Range>;

std::vector<Ranges> rangesList = { 
    {{1, 10}, {20, 30}}, 
    {{3,6}, {8, 25}}, 
    {{2, 5}, {7, 35}} 
};

struct End
{
    RangeT val;
    bool isStart;
};

int numOpened = 0;

bool allOpened()
{
    return numOpened == rangesList.size();
}

RangeT lastStart;

int main()
{
    std::vector<End> ends;
    std::vector<Range> intersections;
    ends.reserve(100);

    for (auto& list : rangesList)
    {
        for (auto& range : list)
        {
            ends.push_back(End{ range.first, true });
            ends.push_back(End{ range.second, false });
        }
    }

    std::sort(ends.begin(), ends.end(), [](End& first, End& second) { return first.val < second.val; });

    for (End& end : ends)
    {
        if (end.isStart)
        {
            ++numOpened;
            if (allOpened())
            {
                lastStart = end.val;
            }
        }
        else
        {
            if (allOpened())
            {
                intersections.push_back(Range{ lastStart, end.val });
            }
            --numOpened;
        }
    }

    for (auto& range : intersections)
    {
        std::cout << '[' << range.first << ',' << range.second << ")\n";
    }
} 
