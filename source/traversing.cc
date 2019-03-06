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


void construct_container (std::vector<int> &container, const unsigned int size)
{
  // Use current time as seed for random generator.
  std::srand(std::time(nullptr));
  container.reserve(size);

  for (int i = 0; i < size; i++)
    container.push_back(std::rand());
}

void construct_container (std::list<int> &container, const unsigned int size)
{
  // Use current time as seed for random generator.
  std::srand(std::time(nullptr));

  for (int i = 0; i < size; i++)
    container.push_back(std::rand());
}

static void escape (void *p)
{
  asm volatile("" : : "g"(p) : "memory");
}

template <typename T>
void BM_traverse(benchmark::State &state)
{
  T container;
  construct_container(container, state.range(0));

  using value_type = typename T::value_type;

  for (auto _ : state)
  {
    // state.PauseTiming();
    // state.ResumeTiming();
    value_type sum = 0;

    for (const auto & element : container)
      sum += element;

    escape (&sum);
  }
}

BENCHMARK_TEMPLATE(BM_traverse, std::vector<int>)->Args({1<<6, 1<<10})
                                                 ->Args({1<<8, 1<<10})
                                                 ->Args({1<<10, 1<<10})
                                                 ->Args({1<<12, 1<<10})
                                                 ->Args({1<<14, 1<<10});
BENCHMARK_TEMPLATE(BM_traverse, std::list<int>)  ->Args({1<<6, 1<<10})
                                                 ->Args({1<<8, 1<<10})
                                                 ->Args({1<<10, 1<<10})
                                                 ->Args({1<<12, 1<<10})
                                                 ->Args({1<<14, 1<<10});

BENCHMARK_MAIN();