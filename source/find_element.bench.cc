/*

*/

#include <vector>
#include <map>
#include <set>
#include <list>

#include <algorithm>

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <benchmark/benchmark.h>


template <typename T>
void BM_push_back(benchmark::State &state)
{
  T container;
  using value_type = typename T::value_type;

  for (auto _ : state)
  {
    for (int i = 0; i < state.range(1); i++)
      container.push_back(static_cast<value_type>(std::rand()));
  }
}

BENCHMARK_TEMPLATE(BM_push_back, std::vector<int>)->Args({1<<10, 1<<10});
//BENCHMARK_TEMPLATE(BM_push_back, std::list<int>)->Args({1<<10, 1<<10});

template <typename T>
void BM_end_insert(benchmark::State &state)
{
  T container;
  using value_type = typename T::value_type;

  for (auto _ : state)
  {
    for (int i = 0; i < state.range(1); i++)
      container.insert(std::end(container),static_cast<value_type>(std::rand()));
  }
}

BENCHMARK_TEMPLATE(BM_end_insert, std::vector<int>)->Args({1<<10, 1<<10});
//BENCHMARK_TEMPLATE(BM_end_insert, std::list<int>)->Args({1<<10, 1<<10});

//BENCHMARK_TEMPLATE(BM_push_back, std::set<int>)->Args({1<<10, 128});

BENCHMARK_MAIN();

