#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include "memoized.hpp"

constexpr uint64_t factorial(uint64_t N)
{
    return N <= 1 ? 1 : N * factorial(N-1);
}

class mem_factorial
{
private:
    std::map<uint64_t, uint64_t> cache;

public:
    mem_factorial()
    {
        cache[0] = cache[1] = 1;
    }
    uint64_t operator()(uint64_t n)
    {
        const auto cached = cache.find(n);

        return cached == cache.end() 
             ? cache[n] = n * (*this)(n - 1)
             : cached->second;
    }
};

#endif
