#include <benchmark/benchmark.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <execution>
#include <vector>
#include <random>

#include <range/v3/view/all.hpp>
#include <range/v3/numeric/accumulate.hpp>

const uint32_t RMul = 10;
const uint32_t RMin = 100;
const uint32_t RMax = 10000000;

auto init(int64_t size)
{
    std::vector<uint32_t> data(static_cast<uint32_t>(size));

    std::seed_seq seq({1, 2, 3, 4, 5});
    seq.generate(data.begin(),data.end());

    return data;
}

static void BM_manual_1(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
    {
        uint64_t media = 0L;

        for (uint64_t k = 0L; k < data.size(); media += data[k++]);

        media /= data.size();
    }
}
BENCHMARK(BM_manual_1)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_manual_2(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
    {
        uint64_t media = 0L;

        for (auto& e : data)
        {
            media += e;
        }
        media /= data.size();
    }
}
BENCHMARK(BM_manual_2)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_manual_3(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
    {
        uint64_t media = 0L;

        for (auto it = data.cbegin(); it != data.cend(); ++it)
        {
            media += *it;
        }
        media /= data.size();
    }
}
BENCHMARK(BM_manual_3)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_accumulate(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
        uint64_t media = std::accumulate(data.cbegin(), data.cend(),
                                        static_cast<decltype(media)>(0))
                       / data.size();
}
BENCHMARK(BM_accumulate)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_reduce_seq(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
        uint64_t media = std::reduce(std::execution::seq,
                                     data.cbegin(), data.cend(),
                                     static_cast<decltype(media)>(0))
                       / data.size();
}
BENCHMARK(BM_reduce_seq)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_reduce_unseq(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
        uint64_t media = std::reduce(std::execution::unseq,
                                     data.cbegin(), data.cend(),
                                     static_cast<decltype(media)>(0))
                       / data.size();
}
BENCHMARK(BM_reduce_unseq)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_reduce_par(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
        uint64_t media = std::reduce(std::execution::par,
                                     data.cbegin(), data.cend(),
                                     static_cast<decltype(media)>(0))
                       / data.size();
}
BENCHMARK(BM_reduce_par)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_reduce_par_unseq(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
        uint64_t media = std::reduce(std::execution::par_unseq,
                                     data.cbegin(), data.cend(),
                                     static_cast<decltype(media)>(0))
                       / data.size();
}
BENCHMARK(BM_reduce_par_unseq)->RangeMultiplier(RMul)->Range(RMin, RMax);

static void BM_ranges(benchmark::State& state)
{
    std::vector<uint32_t> data = init(state.range(0));

    while(state.KeepRunning())
    {
        uint64_t media = ranges::accumulate(ranges::views::all(data),
                                            static_cast<decltype(media)>(0));
    }
}
BENCHMARK(BM_ranges)->RangeMultiplier(RMul)->Range(RMin, RMax);

BENCHMARK_MAIN();
