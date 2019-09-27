#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include "memoized.hpp"

constexpr uint64_t fibonacci(uint64_t n)
{
	return n <= 1 ? 1
	     	      : fibonacci(n - 1) + fibonacci(n - 2);
}

#endif
