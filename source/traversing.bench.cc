/*

*/

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <list>

#include <benchmark/benchmark.h>

#include "../include/utilities.h"

template <typename ContainerType>
void BM_traverse(benchmark::State &state)
{
  ContainerType container;

  container.resize(state.range(0));

  const unsigned int maximum_element_value = state.range(1);
  fill_random (container, maximum_element_value);

  for (auto _ : state)
  {
    // state.PauseTiming();
    // state.ResumeTiming();
    typename ContainerType::value_type sum = 0;

    for (const auto & element : container)
      benchmark::DoNotOptimize(sum += element);
  }
}

#define BENCHMARK_TEMPLATE_TYPE(T) \
  BENCHMARK_TEMPLATE(BM_traverse, T)->Args({1<<6, 1<<10})  \
                                    ->Args({1<<8, 1<<10})  \
                                    ->Args({1<<10, 1<<10}) \
                                    ->Args({1<<12, 1<<10}) \
                                    ->Args({1<<14, 1<<10});

BENCHMARK_TEMPLATE_TYPE(std::vector<int>);
BENCHMARK_TEMPLATE_TYPE(std::list<int>);

BENCHMARK_MAIN();