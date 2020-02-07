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
            //[[maybe_unused]] auto result = 
            benchmark::DoNotOptimize(
                fibonacci(k)
            );
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
            //[[maybe_unused]] auto result = 
            benchmark::DoNotOptimize(
                memoized_fibonacci(k)
            );
    }
}
BENCHMARK(BM_Memoized_fibonacci)->RangeMultiplier(RMul)->Range(RMin, RMax);

auto recursive_memoized_fibonacci = make_memoized_r<uint64_t(uint64_t)>(
    [](auto& f, uint64_t n) {
        return n == 0 ? 0
                : n == 1 ? 1
                : f(n - 1) + f(n - 2);
    });

static void BM_RecursiveMemoized_fibonacci(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        uint64_t max = static_cast<uint64_t>(state.range(0));
        for (uint64_t k = 0;k <= max; ++k)
            //[[maybe_unused]] auto result = 
            benchmark::DoNotOptimize(
                recursive_memoized_fibonacci(k)
            );
    }
}
BENCHMARK(BM_RecursiveMemoized_fibonacci)->RangeMultiplier(RMul)->Range(RMin, RMax);

mem_fibonacci cached_fibonacci;

static void BM_Cached_fibonacci(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        uint64_t max = static_cast<uint64_t>(state.range(0));
        for (uint64_t k = 0;k <= max; ++k)
            //[[maybe_unused]] auto result = 
            benchmark::DoNotOptimize(
                cached_fibonacci(k)
            );
    }
}
BENCHMARK(BM_Cached_fibonacci)->RangeMultiplier(RMul)->Range(RMin, RMax);

BENCHMARK_MAIN();
