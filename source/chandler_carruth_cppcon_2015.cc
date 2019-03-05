
/*
 Comments

 Allocation in the std::vector<>::push_back() is conditional
 that a compiler doesn't observe.
 Allocation in reserve is easier for the compiler to observe.
*/

#include <vector>
#include <map>
#include <set>

#include <iostream>

#include <benchmark/benchmark.h>

static void escape(void *p)
{
  asm volatile("" : : "g"(p) : "memory");
}

static void clobber()
{
  asm volatile("" : : : "memory");
}

static void BM_create(benchmark::State& state)
{
  while (state.KeepRunning())
  {
    std::vector<int> v;
    escape(&v);
    (void)v;
  }
}

BENCHMARK(BM_create);

static void BM_reserve(benchmark::State& state)
{
  while (state.KeepRunning())
  {
    std::vector<int> v;
    v.reserve(1);
    //escape(v.data());
  }
}

BENCHMARK(BM_reserve);

static void BM_push_back(benchmark::State& state)
{
  while (state.KeepRunning())
  {
    std::vector<int> v;
    //escape(v.data());
    v.push_back(42);
    //clobber();
  }
}

// Register the function as a benchmark
BENCHMARK(BM_push_back);

static void BM_reserve_push_back(benchmark::State& state)
{
  while (state.KeepRunning())
  {
    std::vector<int> v;
    v.reserve(1);
    //escape(v.data());
    v.push_back(42);
    //clobber();
  }
}

// Register the function as a benchmark
BENCHMARK(BM_reserve_push_back);

BENCHMARK_MAIN();