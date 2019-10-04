#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include "memoized.hpp"
#include <vector>

constexpr uint64_t factorial(uint64_t N)
{
    return N <= 1 ? 1 : N * factorial(N-1);
}

class mem_factorial
{
private:
    std::vector<uint64_t> cache;
    std::recursive_mutex m_cache_mutex;

public:
    mem_factorial() : cache(2)
    {
        cache[0] = cache[1] = 1;
    }
    uint64_t operator()(uint64_t n)
    {
        std::unique_lock<std::recursive_mutex>
                lock{m_cache_mutex};

        if (cache.size() <= n)
        {
            auto fn = n * (*this)(n - 1);
            cache.resize(n+1);
            cache[n] = fn;
        }
        return cache[n];
    }
};

#endif
