//
// Testing factorial functions
// Copyright (C) 2020 Giulio Guarnone
//
#include <cmath>
#include <fmt/format.h>
#include "factorial.hpp"


int main()
{
    auto memoized_factorial = make_memoized(factorial);

    auto recursive_memoized_factorial = make_memoized_r<uint64_t(uint64_t)>(
        [](auto& factorial, uint64_t n) {
            return n == 1 ? 1
                 : n * factorial(n - 1);
        });

    mem_factorial mem_fact;

    fmt::print("Calcolo fattoriale : N!\n");
    fmt::print("{}! = {}\n",  2, factorial( 2));
    fmt::print("{}! = {}\n",  4, factorial( 4));
    fmt::print("{}! = {}\n",  8, factorial( 8));
    fmt::print("{}! = {}\n", 16, factorial(16));
    fmt::print("\n");
    fmt::print("Calcolo fattoriale ottimizzato (memoization generica) : N!\n");
    fmt::print("{}! = {}\n",  2, memoized_factorial( 2));
    fmt::print("{}! = {}\n",  4, memoized_factorial( 4));
    fmt::print("{}! = {}\n",  8, memoized_factorial( 8));
    fmt::print("{}! = {}\n", 16, memoized_factorial(16));
    fmt::print("{}! = {}\n", 32, memoized_factorial(32));
    fmt::print("\n");
    fmt::print("Calcolo fattoriale ottimizzato (memoization ricorsiva) : N!\n");
    fmt::print("{}! = {}\n",  2, recursive_memoized_factorial( 2));
    fmt::print("{}! = {}\n",  4, recursive_memoized_factorial( 4));
    fmt::print("{}! = {}\n",  8, recursive_memoized_factorial( 8));
    fmt::print("{}! = {}\n", 16, recursive_memoized_factorial(16));
    fmt::print("{}! = {}\n", 32, recursive_memoized_factorial(32));
    fmt::print("\n");
    fmt::print("Calcolo fattoriale custom (memoization specializzata) : N!\n");
    fmt::print("{}! = {}\n",  2, mem_fact( 2));
    fmt::print("{}! = {}\n",  4, mem_fact( 4));
    fmt::print("{}! = {}\n",  8, mem_fact( 8));
    fmt::print("{}! = {}\n", 16, mem_fact(16));
    fmt::print("{}! = {}\n", 32, mem_fact(32));
    fmt::print("\n");
    fmt::print("Calcolo fattoriale : tgamma(N+1)\n");
    fmt::print("tgamma({}+1) = {}\n",  2, static_cast<uint64_t>(std::tgamma(static_cast<long double>( 2+1))));
    fmt::print("tgamma({}+1) = {}\n",  4, static_cast<uint64_t>(std::tgamma(static_cast<long double>( 4+1))));
    fmt::print("tgamma({}+1) = {}\n",  8, static_cast<uint64_t>(std::tgamma(static_cast<long double>( 8+1))));
    fmt::print("tgamma({}+1) = {}\n", 16, static_cast<uint64_t>(std::tgamma(static_cast<long double>(16+1))));
}
