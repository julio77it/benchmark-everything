#include <benchmark/benchmark.h>
#include <vector>

const uint32_t MinLen = 4;
const uint32_t MaxLen = 2;

static void BM_StringCreation(benchmark::State& state)
{
	for (auto _ : state)
	{
		{
		std::string empty_string;
		}
	}
}
BENCHMARK(BM_StringCreation);

static void BM_StringCopy(benchmark::State& state)
{
	const std::string test(static_cast<std::size_t>(state.range(0)), 'a');
	const std::vector<std::string> x(state.max_iterations, test);
	std::size_t s = 0;

	for (auto _ : state)
		std::string copy(x[s++]);
}
BENCHMARK(BM_StringCopy)->Arg(MinLen);
BENCHMARK(BM_StringCopy)->Arg(MaxLen);

static void BM_StringMoveCopy(benchmark::State& state)
{
	const std::string test(static_cast<std::size_t>(state.range(0)), 'a');
	std::vector<std::string> x(state.max_iterations, test);
	std::size_t s = 0;

	for (auto _ : state)
		std::string copy(std::move(x[s++]));
}
BENCHMARK(BM_StringMoveCopy)->Arg(MinLen);
BENCHMARK(BM_StringMoveCopy)->Arg(MaxLen);

static void BM_StringAssign(benchmark::State& state)
{
	const std::string test(static_cast<std::size_t>(state.range(0)), 'a');
	const std::vector<std::string> x(state.max_iterations, test);
	std::size_t s = 0;

	for (auto _ : state)
	{
		{
		std::string assign;
		assign = x[s++];
		}
	}
}
BENCHMARK(BM_StringAssign)->Arg(MinLen);
BENCHMARK(BM_StringAssign)->Arg(MaxLen);

static void BM_StringMoveAssign(benchmark::State& state)
{
	const std::string test(static_cast<std::size_t>(state.range(0)), 'a');
	std::vector<std::string> x(state.max_iterations, test);
	std::size_t s = 0;

	for (auto _ : state)
	{
		{
		std::string assign;
		assign = std::move(x[s++]);
		}
	}
}
BENCHMARK(BM_StringMoveAssign)->Arg(MinLen);
BENCHMARK(BM_StringMoveAssign)->Arg(MaxLen);

BENCHMARK_MAIN();
