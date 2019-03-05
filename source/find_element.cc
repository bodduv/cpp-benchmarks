/*

*/

#include <vector>
#include <map>
#include <set>
#include <list>


#include <iostream>

#include <benchmark/benchmark.h>

template <typename T>
void BM_insert(benchmark::State &state)
{
  T container;
  for (auto _ : state)
  {
    state.PauseTiming();
    for (int i = 0; i < state.range(0); i++)
      container.push_back(RandomNumber());
    state.ResumeTiming();
    for (int i = 0; i < state.range(1); i++)
      container.push_back(RandomNumber());
  }
}

BENCHMARK_TEMPLATE(BM_insert, vector<int>)->Args({1<<10, 128})

BENCHMARK_MAIN();