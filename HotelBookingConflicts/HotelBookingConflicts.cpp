// HotelBookingConflicts.cpp : 
// Find all conflicts in list of hotel's bokings (start, end)
//

#include <iostream>
#include <vector>
#include <algorithm>

struct Booking
{
    int start;
    int end;
};

std::vector<Booking> bookings = { {4, 5}, {3, 6}, {1, 5}, {1, 2}, {2, 3}  };

std::ostream& operator << (std::ostream& os, const Booking& booking);

int main()
{
    std::cout << "start\n";

    std::sort(bookings.begin(), bookings.end(), [](auto& first, auto& second) { return first.start < second.start; });

    for (auto it = bookings .cbegin(); it != bookings.cend(); ++it)
    {
        for (auto it_conflicts = it + 1; it_conflicts != bookings.cend() && it_conflicts->start < it->end; ++it_conflicts) {
            // conflict found
            auto end_of_conflict = std::min(it->end, it_conflicts->end);
            std::cout << "conflict found between " << *it << " and " << *it_conflicts << " [" << it_conflicts->start << "-" << end_of_conflict << "]\n";
        }
    }

    std::cout << "end\n";
}

std::ostream& operator << (std::ostream& os, const Booking& booking)
{
    os << '{' << booking.start << ", " << booking.end << '}';
    return os;
}