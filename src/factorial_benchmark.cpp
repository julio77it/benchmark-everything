//
// Benchmarking factorial functions
// Copyright (C) 2020 Giulio Guarnone
//
#include <benchmark/benchmark.h>
#include <cmath>
#include "factorial.hpp"


static void BM_Factorial(benchmark::State& state)
{
    uint64_t n = static_cast<uint64_t>(state.range(0));

    while (state.KeepRunning())
    {
        //[[maybe_unused]] auto r =
        benchmark::DoNotOptimize(
            factorial(n)
        );
    }
}
BENCHMARK(BM_Factorial)->RangeMultiplier(2)->Range(2, 16);

auto memoized_factorial = make_memoized(factorial);

static void BM_MemoizedFactorial(benchmark::State& state)
{
    uint32_t n = static_cast<uint32_t>(state.range(0));

    while (state.KeepRunning())
    {
        //[[maybe_unused]] auto r =
        benchmark::DoNotOptimize(
            memoized_factorial(n)
        );
    }
}
BENCHMARK(BM_MemoizedFactorial)->RangeMultiplier(2)->Range(2, 16);

auto recursive_memoized_factorial = make_memoized_r<uint64_t(uint64_t)>(
    [](auto& factorial, uint64_t n) {
        return n <= 1
             ? 1
             : n * factorial(n - 1);
    });

static void BM_RecursiveMemoizedFactorial(benchmark::State& state)
{
    uint32_t n = static_cast<uint32_t>(state.range(0));

    while (state.KeepRunning())
    {
        //[[maybe_unused]] auto r =
        benchmark::DoNotOptimize(
            recursive_memoized_factorial(n)
        );
    }
}
BENCHMARK(BM_RecursiveMemoizedFactorial)->RangeMultiplier(2)->Range(2, 16);

mem_factorial mem_fact;

static void BM_CachedFactorial(benchmark::State& state)
{
    uint32_t n = static_cast<uint32_t>(state.range(0));

    while (state.KeepRunning())
    {
        //[[maybe_unused]] auto r =
        benchmark::DoNotOptimize(
            mem_fact(n)
        );
    }
}
BENCHMARK(BM_CachedFactorial)->RangeMultiplier(2)->Range(2, 16);

static void BM_TGamma(benchmark::State& state)
{
    uint64_t n = static_cast<uint64_t>(state.range(0));

    while (state.KeepRunning())
    {
        //[[maybe_unused]] auto r =
        benchmark::DoNotOptimize(
            static_cast<decltype(n)>(std::tgammal(n+1))
        );
    }
}
BENCHMARK(BM_TGamma)->RangeMultiplier(2)->Range(2, 16);

BENCHMARK_MAIN();
