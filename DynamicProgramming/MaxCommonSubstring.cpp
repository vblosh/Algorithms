#include "stdafx.h"
#include <assert.h>
#include "Header.h"

template <typename T>
class matrix
{
    std::vector<T> inner_;
    unsigned int dimx_, dimy_;

public:
    matrix(unsigned int dimy, unsigned int dimx)
        : dimx_(dimx), dimy_(dimy)
    {
        inner_.resize(dimx_ * dimy_);
    }

    T& operator()(unsigned int y, unsigned int x)
    {
        return inner_[dimx_ * y + x];
    }

    T& at(unsigned int y, unsigned int x)
    {
        if (x >= dimx_ || y >= dimy_)
            throw std::out_of_range("matrix indices out of range"); // ouch
        return this->operator()(x, y);
    }
};

std::string MaxCommonSunstring(std::string str1, std::string str2)
{
    matrix<unsigned char> sol_tbl(str2.size()+1, str1.size()+1);
    size_t str1end; // end of max subsring in str1
    size_t str2end; // end of max subsring in str2

    // fill first row and column
    for (size_t i = 0; i <= str1.size(); i++)
    {
        sol_tbl(0, i) = 0;
    }
    for (size_t i = 0; i <= str2.size(); i++)
    {
        sol_tbl(i, 0) = 0;
    }

    for (size_t i = 1; i <= str2.size(); i++)
    {
        for (size_t j = 1; j <= str1.size(); j++)
        {
            if (str1[j - 1] == str2[i - 1])
            {
                sol_tbl(i, j) = sol_tbl(i - 1, j - 1) + 1;
                str1end = j - 1;
                str2end = i - 1;
            }
            else
            {
                if (sol_tbl(i - 1, j) > sol_tbl(i, j - 1))
                {
                    sol_tbl(i, j) = sol_tbl(i - 1, j);
                    str1end = j - 1;
                    str2end = i - 1 - 1;
                }
                else
                {
                    sol_tbl(i, j) = sol_tbl(i, j - 1);
                    str1end = j - 1 - 1;
                    str2end = i - 1;
                }
            }
        }
    }
    size_t max_subst_len = sol_tbl(str2.size(), str1.size());

    assert(str1.substr(str1end - max_subst_len, max_subst_len) == str2.substr(str2end - max_subst_len, max_subst_len));
    return str1.substr(str1end - max_subst_len, max_subst_len);
}
