//
// fibonacci functions
// Copyright (C) 2020 Giulio Guarnone
//
#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include "memoized.hpp"

#include <vector>

constexpr uint64_t fibonacci(uint64_t n)
{
	return n == 0 || n == 1 ? n
	     	      : fibonacci(n - 1) + fibonacci(n - 2);
}

class mem_fibonacci
{
private:
    std::vector<uint64_t> cache;
    std::recursive_mutex m_cache_mutex;

public:
    mem_fibonacci() : cache(2)
    {
        cache[0] = 0;
        cache[1] = 1;
    }
    uint64_t operator()(uint64_t n)
    {
        std::unique_lock<std::recursive_mutex>
            lock{m_cache_mutex};

        if (cache.size() <= n)
        {
            uint64_t fb = (*this)(n - 1) + (*this)(n - 2);

            cache.resize(n+1);
            cache[n] = fb;
        }
        return cache[n];
    }
};

#endif
