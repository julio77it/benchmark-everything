#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include "memoized.hpp"

constexpr uint64_t fibonacci(uint64_t n)
{
	return n <= 1 ? 1
	     	      : fibonacci(n - 1) + fibonacci(n - 2);
}

class mem_fibonacci
{
private:
    std::map<uint64_t, uint64_t> cache;

public:
    mem_fibonacci()
    {
        cache[0] = cache[1] = 1;
    }
    uint64_t operator()(uint64_t n)
    {
        const auto cached = cache.find(n);

        return cached == cache.end() 
             ? cache[n] = (*this)(n - 1) + (*this)(n - 2)
             : cached->second;
    }
};

#endif
