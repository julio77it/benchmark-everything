#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include "memoized.hpp"

constexpr uint64_t factorial(uint64_t N)
{
    return N <= 1 ? 1 : N * factorial(N-1);
}

#endif
