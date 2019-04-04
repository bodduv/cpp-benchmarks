#include <benchmark/benchmark.h>
#include <limits>
#include <vector>
#include <../include/utilities.h>

/**
 * Chandler Carruth : CppCon 2017
 * Benchmark specifically designed to understand bad data structure or
 * cache locality problems.
 */

static void BM_cache(benchmark::State &state)
{
  // Get an amount of memory/space we want to use in this benchmark.
  int n_bytes = 1 << state.range(0);

  // Count the number of elements that can fit in `n_bytes`,
  // given that we also need to store indices.
  int n_elements = (n_bytes/ sizeof(int));

  std::vector<int> v, indices;

  RandomDevice rd;
  using size_type = typename std::vector<int>::size_type;

  for (size_type i = 0; i < n_elements; ++i)
    v.push_back(rd.get_random_number<int> (std::numeric_limits<int>::min(),
                                           std::numeric_limits<int>::max()));

  for (size_type i = 0; i < n_elements; ++i)
    indices.push_back(rd.get_random_number<int> (0, n_elements));

  for (auto _ : state)
  {
    long sum = 0;

    // Access pattern through `indices` undermines cache locality.
    for (int i : indices)
      sum += v[i];
    benchmark::DoNotOptimize(sum);
  }

  state.SetBytesProcessed(long(state.iterations())*long(n_bytes));
  state.SetLabel(std::to_string(n_bytes / 1024) + "kb");
}

static void BM_clamp(benchmark::State &state)
{
  int size = state.range(0);
  std::vector<int> v;

  RandomDevice rd;

  for (int i = 0; i < size; ++i)
    v.push_back(rd.get_random_number(0,std::numeric_limits<int>::max()));

  for (auto _ : state)
  {
    for (int &i : v)
      i = i > 255 ? 255 : i;
    benchmark::DoNotOptimize(v);
  }
  state.SetItemsProcessed(long(state.iterations()) * long(v.size()));
}

//BENCHMARK(BM_cache)->DenseRange(13,26)->ReportAggregatesOnly(true);
BENCHMARK(BM_clamp)->Range(1<<10,1<<20)->ReportAggregatesOnly(true);

BENCHMARK_MAIN();







