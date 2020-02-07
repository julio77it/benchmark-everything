#include <benchmark/benchmark.h>
#include "partition.hpp"

static void BM_partition_simple(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_simple(input);
    }
}
BENCHMARK(BM_partition_simple);

static void BM_partition_transform(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_transform(input);
    }
}
BENCHMARK(BM_partition_transform);

static void BM_partition_multiset(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_multiset(input);
    }
}
BENCHMARK(BM_partition_multiset);

static void BM_partition_sortsquares(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_sortsquares(input);
    }
}
BENCHMARK(BM_partition_sortsquares);

static void BM_partition_final_draft(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_final_draft(input);
    }
}
BENCHMARK(BM_partition_final_draft);

static void BM_partition_final_optimized(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_final_optimized(input);
    }
}
BENCHMARK(BM_partition_final_optimized);

#ifdef __cplusplus >= 201803L
static void BM_partition_final_cxx20(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_final_cxx20(input);
    }
}
BENCHMARK(BM_partition_final_cxx20);
#endif

static void BM_partition_final_range_1st(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_final_range_1st(input);
    }
}
BENCHMARK(BM_partition_final_range_1st);

static void BM_partition_final_range_2nd(benchmark::State& state)
{
    std::vector<int> input = {-4, -2,  0,  1,  5}; 

    while(state.KeepRunning())
    {
        [[maybe_unused]] auto res = partition_final_range_2nd(input);
    }
}
BENCHMARK(BM_partition_final_range_2nd);

BENCHMARK_MAIN();