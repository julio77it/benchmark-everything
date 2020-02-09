//
// Benchmarking immer
// Copyright (C) 2020 Giulio Guarnone
//
#include <benchmark/benchmark.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <immer/vector.hpp>
#include <immer/flex_vector.hpp>

using test_type = int;

template<typename T>
T gen()
{
    static T value;

    return ++value;
}

static void BM_StdVector_BackInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        std::vector<test_type> v;

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void BM_StdVector_BackInsertSized(benchmark::State& state)
{
	for (auto _ : state)
	{
        std::vector<test_type> v(state.range(0));

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void BM_StdVector_MiddleInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        std::vector<test_type> v{gen<test_type>(), gen<test_type>()};

		for (auto k = 0;k < state.range(0); ++k)
		{
			[[maybe_unused]] auto r = v.insert(v.begin(), gen<test_type>());
		}
        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}

static void BM_StdVector_IteratorVisit(benchmark::State& state)
{
	std::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		for (auto it = v.cbegin(); it != v.cend(); ++it)
		{
			[[maybe_unused]] auto e = *it;
		}
	}
}
static void BM_StdVector_AlgorithmVisit(benchmark::State& state)
{
	std::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		std::for_each(v.cbegin(), v.cend(), [](auto e){ [[maybe_unused]] auto i = e; });
	}
}
static void BM_ImmerVector_Default_BackInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v;

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void BM_ImmerVector_Default_BackInsertSized(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v(state.range(0));

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
/*
static void BM_ImmerVector_Transient_BackInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v{1, 2, 3};

        auto t = v.transient();

        std::generate_n(std::back_inserter(t), state.range(0), gen<test_type>);

        v = t.persistent();
	}
}
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(10);
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(100);
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(1000);
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(10000);
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(100000);
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(1000000);
BENCHMARK(BM_ImmerVector_Transient_BackInsertRaw)->Arg(10000000);
*/
static void BM_ImmerFlexVector_Default_MiddleInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::flex_vector<test_type> v{gen<test_type>(), gen<test_type>()};

		for (auto k = 0;k < state.range(0); ++k)
		{
			[[maybe_unused]] auto r = v.insert(1, gen<test_type>());
		}
	}
}


static void BM_ImmerVector_Default_IteratorVisit(benchmark::State& state)
{
	immer::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			[[maybe_unused]] auto e = *it;
		}
	}
}
static void BM_ImmerVector_Default_AlgorithmVisit(benchmark::State& state)
{
	immer::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		std::for_each(v.begin(), v.end(), [](auto e){ [[maybe_unused]] auto i = e; });
	}
}




BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(10);
BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(100);
BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(1000);
BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(10000);
BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(100000);
BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(1000000);
BENCHMARK(BM_StdVector_BackInsertRaw)->Arg(10000000);

BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(10);
BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(100);
BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(1000);
BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(10000);
BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(100000);
BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(1000000);
BENCHMARK(BM_ImmerVector_Default_BackInsertRaw)->Arg(10000000);


BENCHMARK(BM_StdVector_BackInsertSized)->Arg(10);
BENCHMARK(BM_StdVector_BackInsertSized)->Arg(100);
BENCHMARK(BM_StdVector_BackInsertSized)->Arg(1000);
BENCHMARK(BM_StdVector_BackInsertSized)->Arg(10000);
BENCHMARK(BM_StdVector_BackInsertSized)->Arg(100000);
BENCHMARK(BM_StdVector_BackInsertSized)->Arg(1000000);
BENCHMARK(BM_StdVector_BackInsertSized)->Arg(10000000);

BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(10);
BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(100);
BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(1000);
BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(10000);
BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(100000);
BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(1000000);
BENCHMARK(BM_ImmerVector_Default_BackInsertSized)->Arg(10000000);



BENCHMARK(BM_StdVector_MiddleInsertRaw)->Arg(10);
BENCHMARK(BM_StdVector_MiddleInsertRaw)->Arg(100);
BENCHMARK(BM_StdVector_MiddleInsertRaw)->Arg(1000);
BENCHMARK(BM_StdVector_MiddleInsertRaw)->Arg(10000);
BENCHMARK(BM_StdVector_MiddleInsertRaw)->Arg(100000);

BENCHMARK(BM_ImmerFlexVector_Default_MiddleInsertRaw)->Arg(10);
BENCHMARK(BM_ImmerFlexVector_Default_MiddleInsertRaw)->Arg(100);
BENCHMARK(BM_ImmerFlexVector_Default_MiddleInsertRaw)->Arg(1000);
BENCHMARK(BM_ImmerFlexVector_Default_MiddleInsertRaw)->Arg(10000);
BENCHMARK(BM_ImmerFlexVector_Default_MiddleInsertRaw)->Arg(100000);



BENCHMARK(BM_StdVector_IteratorVisit)->Arg(10);
BENCHMARK(BM_StdVector_IteratorVisit)->Arg(100);
BENCHMARK(BM_StdVector_IteratorVisit)->Arg(1000);
BENCHMARK(BM_StdVector_IteratorVisit)->Arg(10000);
BENCHMARK(BM_StdVector_IteratorVisit)->Arg(100000);
BENCHMARK(BM_StdVector_IteratorVisit)->Arg(1000000);
BENCHMARK(BM_StdVector_IteratorVisit)->Arg(10000000);

BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(10);
BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(100);
BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(1000);
BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(10000);
BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(100000);
BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(1000000);
BENCHMARK(BM_ImmerVector_Default_IteratorVisit)->Arg(10000000);




BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(10);
BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(100);
BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(1000);
BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(10000);
BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(100000);
BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(1000000);
BENCHMARK(BM_StdVector_AlgorithmVisit)->Arg(10000000);

BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(10);
BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(100);
BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(1000);
BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(10000);
BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(100000);
BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(1000000);
BENCHMARK(BM_ImmerVector_Default_AlgorithmVisit)->Arg(10000000);

BENCHMARK_MAIN();
