#include <cmath>
#include <fmt/format.h>
#include "fibonacci.hpp"

int main()
{
    fmt::print("Fibonacci\n");
    fmt::print("f({}) = {}\n",  15, fibonacci( 15));
    fmt::print("f({}) = {}\n",  14, fibonacci( 14));
    fmt::print("\n");

    auto memoized_fibonacci = make_memoized(fibonacci);

    fmt::print("Fibonacci ottimizzato\n");
    fmt::print("f({}) = {}\n",  15, memoized_fibonacci( 15));
    fmt::print("f({}) = {}\n",  14, memoized_fibonacci( 14));
}
