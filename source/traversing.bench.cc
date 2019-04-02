/*

  // Cleanup the following:

  Traversing std::list isn't as fast as std::vector due to pointer chasing
  behavior, i.e. in order to get to the next element from a given element
  we need to follow a pointer which bares an overhead.

  Conclusions:
  - Traversing std::list is slower than traversing std::vector by
    a factor of 8.

*/

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <list>

#include <benchmark/benchmark.h>

#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/stream.hpp>

#include "../include/utilities.h"

template <typename ContainerType>
void BM_traverse(benchmark::State &state)
{
  ContainerType container;

  fill_random (container,
               state.range(0)/*container_size*/,
               state.range(1) /* max_element_value*/);

  for(auto _ : state)
  {
    typename ContainerType::value_type sum = 0;

    for (const auto & element : container)
      benchmark::DoNotOptimize(sum += element);
      // If benchmark::DonotOptimize() is not used,
      // then the compiler will skip summation computations
  }

  // Compute asymptotic complexity given the size of the container.
  state.SetComplexityN(state.range(0));
}

template <typename ContainerType>
void BM_traverse_optimize(benchmark::State &state)
{
  ContainerType container;

  fill_random (container,
               state.range(0)/*container_size*/,
               state.range(1) /* max_element_value*/);

  boost::iostreams::stream<boost::iostreams::null_sink>
    null_out {boost::iostreams::null_sink{}};

  for(auto _ : state)
  {
    typename ContainerType::value_type sum = 0;

    for (const auto & element : container)
      sum += element;

    null_out << sum;
    // Inorder to not let compiler skip summation computations.
  }

  // Compute asymptotic complexity given the size of the container.
  state.SetComplexityN(state.range(0));
}

#define BENCHMARK_TEMPLATE_TYPE1(T) \
  BENCHMARK_TEMPLATE(BM_traverse, T)->Ranges({{1<<6, 1<< 14}, {1<<10, 1<<10}}) \
                                    ->Complexity(benchmark::oN);

#define BENCHMARK_TEMPLATE_TYPE2(T) \
  BENCHMARK_TEMPLATE(BM_traverse_optimize, T)->Ranges({{1<<6, 1<< 14}, {1<<10, 1<<10}}) \
                                             ->Complexity(benchmark::oN);

BENCHMARK_TEMPLATE_TYPE1(std::vector<int>);
BENCHMARK_TEMPLATE_TYPE2(std::vector<int>);
BENCHMARK_TEMPLATE_TYPE1(std::list<int>);
BENCHMARK_TEMPLATE_TYPE2(std::list<int>);

BENCHMARK_MAIN();