#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "dict_correctness_test.h"
//#include "dict_speed_test.h"
#include "benchmark/benchmark.h"

using namespace std;


static void BM_ZipTreeInsertRand(benchmark::State& state) {
  ZipTree z;
  for (auto _ : state) {
    state.PauseTiming();
    for (int j = 0; j < state.range(0); ++j) {
      z.insert(rand(), 0);
    }
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j) {
      z.insert(rand(), 0);
    }
  }
}

BENCHMARK(BM_ZipTreeInsertRand)->Ranges({{1<<10, 8<<10}, {128, 512}});

BENCHMARK_MAIN();
