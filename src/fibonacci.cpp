#include <cmath>
#include <fmt/format.h>
#include "fibonacci.hpp"

int main()
{
    fmt::print("Fibonacci\n");
    fmt::print("f({}) = {}\n",  15, fibonacci( 15));
    fmt::print("f({}) = {}\n",  14, fibonacci( 14));
    fmt::print("f({}) = {}\n",  13, fibonacci( 13));

    auto memoized_fibonacci = make_memoized(fibonacci);

    fmt::print("Fibonacci ottimizzato (memoization generica)\n");
    fmt::print("f({}) = {}\n",  15, memoized_fibonacci( 15));
    fmt::print("f({}) = {}\n",  14, memoized_fibonacci( 14));
    fmt::print("f({}) = {}\n",  13, memoized_fibonacci( 13));

    auto recursive_memoized_fibonacci = make_memoized_r<uint64_t(uint64_t)>(
        [](auto& f, uint64_t n) {
            return n == 0 ? 0
                 : n == 1 ? 1
                 : f(n - 1) + f(n - 2);
        });

    fmt::print("Fibonacci ottimizzato (memoization ricorsiva)\n");
    fmt::print("f({}) = {}\n",  15, recursive_memoized_fibonacci( 15));
    fmt::print("f({}) = {}\n",  14, recursive_memoized_fibonacci( 14));
    fmt::print("f({}) = {}\n",  13, recursive_memoized_fibonacci( 13));

    mem_fibonacci mfibonacci;

    fmt::print("Fibonacci ottimizzato (memoization specializzata)\n");
    fmt::print("f({}) = {}\n",  15, mfibonacci( 15));
    fmt::print("f({}) = {}\n",  14, mfibonacci( 14));
    fmt::print("f({}) = {}\n",  13, mfibonacci( 13));
}
