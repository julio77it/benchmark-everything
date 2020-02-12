//
// Benchmarking immer
// Copyright (C) 2020 Giulio Guarnone
//
#include <benchmark/benchmark.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <immer/vector.hpp>
#include <immer/vector_transient.hpp>
#include <immer/flex_vector.hpp>
#include <immer/flex_vector_transient.hpp>
#include <immer/algorithm.hpp>

using test_type = int;

template<typename T>
T gen()
{
    static T value;

    return ++value;
}

static void StdVect_BackInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        std::vector<test_type> v;

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void StdVect_BackInsertSized(benchmark::State& state)
{
	for (auto _ : state)
	{
        std::vector<test_type> v(state.range(0));

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void StdVect_MiddleInsertRaw(benchmark::State& state)
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
static void StdVect_IteratorVisit(benchmark::State& state)
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
static void StdVect_StdAlgorithmVisit(benchmark::State& state)
{
	std::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		std::for_each(v.cbegin(), v.cend(), [](auto e){ [[maybe_unused]] auto i = e; });
	}
}


static void ImmerVect_Dflt_BackInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v;

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void ImmerVect_Dflt_BackInsertSized(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v(state.range(0));

        std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);
	}
}
static void ImmerVect_Transient_BackInsertRaw(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v{1, 2, 3};

        auto t = v.transient();

        std::generate_n(std::back_inserter(t), state.range(0), gen<test_type>);

        v = t.persistent();
	}
}
static void ImmerVect_Transient_BackInsertSized(benchmark::State& state)
{
	for (auto _ : state)
	{
        immer::vector<test_type> v(state.range(0));

        auto t = v.transient();

        std::generate_n(std::back_inserter(t), state.range(0), gen<test_type>);

        v = t.persistent();
	}
}
static void ImmerFlexVect_Dflt_MiddleInsertRaw(benchmark::State& state)
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
static void ImmerVect_Dflt_IteratorVisit(benchmark::State& state)
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
static void ImmerVect_Dflt_StdAlgorithmVisit(benchmark::State& state)
{
	immer::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		std::for_each(v.begin(), v.end(), [](auto e){ [[maybe_unused]] auto i = e; });
	}
}
static void ImmerVect_Dflt_ImmerAlgorithmVisit(benchmark::State& state)
{
	immer::vector<test_type> v(state.range(0));

	std::generate_n(std::back_inserter(v), state.range(0), gen<test_type>);

	for (auto _ : state)
	{
		immer::for_each(v.begin(), v.end(), [](auto e){ [[maybe_unused]] auto i = e; });
	}
}

//
//
// Benchmark Plan
//
//

//
// Insert At The End on empty vector
//
BENCHMARK(StdVect_BackInsertRaw)->Arg(10);
BENCHMARK(StdVect_BackInsertRaw)->Arg(100);
BENCHMARK(StdVect_BackInsertRaw)->Arg(1000);
BENCHMARK(StdVect_BackInsertRaw)->Arg(10000);
BENCHMARK(StdVect_BackInsertRaw)->Arg(100000);
BENCHMARK(StdVect_BackInsertRaw)->Arg(1000000);
BENCHMARK(StdVect_BackInsertRaw)->Arg(10000000);

BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(10);
BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(100);
BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(1000);
BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(10000);
BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(100000);
BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(1000000);
BENCHMARK(ImmerVect_Dflt_BackInsertRaw)->Arg(10000000);

BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(10);
BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(100);
BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(1000);
BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(10000);
BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(100000);
BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(1000000);
BENCHMARK(ImmerVect_Transient_BackInsertRaw)->Arg(10000000);

//
// Insert At The End on presized vector
//
BENCHMARK(StdVect_BackInsertSized)->Arg(10);
BENCHMARK(StdVect_BackInsertSized)->Arg(100);
BENCHMARK(StdVect_BackInsertSized)->Arg(1000);
BENCHMARK(StdVect_BackInsertSized)->Arg(10000);
BENCHMARK(StdVect_BackInsertSized)->Arg(100000);
BENCHMARK(StdVect_BackInsertSized)->Arg(1000000);
BENCHMARK(StdVect_BackInsertSized)->Arg(10000000);

BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(10);
BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(100);
BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(1000);
BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(10000);
BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(100000);
BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(1000000);
BENCHMARK(ImmerVect_Dflt_BackInsertSized)->Arg(10000000);

BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(10);
BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(100);
BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(1000);
BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(10000);
BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(100000);
BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(1000000);
BENCHMARK(ImmerVect_Transient_BackInsertSized)->Arg(10000000);


//
// Insert in the Middle
//
BENCHMARK(StdVect_MiddleInsertRaw)->Arg(10);
BENCHMARK(StdVect_MiddleInsertRaw)->Arg(100);
BENCHMARK(StdVect_MiddleInsertRaw)->Arg(1000);
BENCHMARK(StdVect_MiddleInsertRaw)->Arg(10000);
BENCHMARK(StdVect_MiddleInsertRaw)->Arg(100000);

BENCHMARK(ImmerFlexVect_Dflt_MiddleInsertRaw)->Arg(10);
BENCHMARK(ImmerFlexVect_Dflt_MiddleInsertRaw)->Arg(100);
BENCHMARK(ImmerFlexVect_Dflt_MiddleInsertRaw)->Arg(1000);
BENCHMARK(ImmerFlexVect_Dflt_MiddleInsertRaw)->Arg(10000);
BENCHMARK(ImmerFlexVect_Dflt_MiddleInsertRaw)->Arg(100000);

//
// Visit By iterator
//
BENCHMARK(StdVect_IteratorVisit)->Arg(10);
BENCHMARK(StdVect_IteratorVisit)->Arg(100);
BENCHMARK(StdVect_IteratorVisit)->Arg(1000);
BENCHMARK(StdVect_IteratorVisit)->Arg(10000);
BENCHMARK(StdVect_IteratorVisit)->Arg(100000);
BENCHMARK(StdVect_IteratorVisit)->Arg(1000000);
BENCHMARK(StdVect_IteratorVisit)->Arg(10000000);

BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(10);
BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(100);
BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(1000);
BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(10000);
BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(100000);
BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(1000000);
BENCHMARK(ImmerVect_Dflt_IteratorVisit)->Arg(10000000);

//
// Visit By for_each
//
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(10);
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(100);
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(1000);
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(10000);
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(100000);
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(1000000);
BENCHMARK(StdVect_StdAlgorithmVisit)->Arg(10000000);

BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(10);
BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(100);
BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(1000);
BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(10000);
BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(100000);
BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(1000000);
BENCHMARK(ImmerVect_Dflt_StdAlgorithmVisit)->Arg(10000000);

BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(10);
BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(100);
BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(1000);
BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(10000);
BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(100000);
BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(1000000);
BENCHMARK(ImmerVect_Dflt_ImmerAlgorithmVisit)->Arg(10000000);




BENCHMARK_MAIN();
