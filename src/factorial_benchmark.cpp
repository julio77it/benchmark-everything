#include <benchmark/benchmark.h>
#include <cmath>
#include "factorial.hpp"


static void BM_Factorial(benchmark::State& state)
{
    uint64_t n = static_cast<uint64_t>(state.range(0));

    while (state.KeepRunning())
    {
        [[maybe_unused]] auto r = factorial(n);
    }
}
BENCHMARK(BM_Factorial)->RangeMultiplier(2)->Range(2, 16);

auto memoized_factorial = make_memoized(factorial);

static void BM_MemoizedFactorial(benchmark::State& state)
{
    uint32_t n = static_cast<uint32_t>(state.range(0));

    while (state.KeepRunning())
    {
        [[maybe_unused]] auto r = memoized_factorial(n);
    }
}
BENCHMARK(BM_MemoizedFactorial)->RangeMultiplier(2)->Range(2, 16);

static void BM_TGamma(benchmark::State& state)
{
    uint64_t n = static_cast<uint64_t>(state.range(0));

    while (state.KeepRunning())
    {
        [[maybe_unused]] auto r = static_cast<decltype(n)>(std::tgammal(n+1));
    }
}
BENCHMARK(BM_TGamma)->RangeMultiplier(2)->Range(2, 16);

BENCHMARK_MAIN();
