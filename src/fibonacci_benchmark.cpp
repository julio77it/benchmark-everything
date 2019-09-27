#include <benchmark/benchmark.h>
#include "fibonacci.hpp"

const uint32_t RMul = 4;
const uint32_t RMin = 2;
const uint32_t RMax = 32;

static void BM_fibonacci(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        uint64_t max = static_cast<uint64_t>(state.range(0));
        for (uint64_t k = 0;k <= max; ++k)
            [[maybe_unused]] auto result = fibonacci(k);
    }
}
BENCHMARK(BM_fibonacci)->RangeMultiplier(RMul)->Range(RMin, RMax);

auto memoized_fibonacci = make_memoized(fibonacci);

static void BM_Memoized_fibonacci(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        uint64_t max = static_cast<uint64_t>(state.range(0));
        for (uint64_t k = 0;k <= max; ++k)
            [[maybe_unused]] auto result = memoized_fibonacci(k);
    }
}
BENCHMARK(BM_Memoized_fibonacci)->RangeMultiplier(RMul)->Range(RMin, RMax);

BENCHMARK_MAIN();
