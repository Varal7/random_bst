#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "dict_correctness_test.h"
//#include "dict_speed_test.h"
#include "benchmark/benchmark.h"

using namespace std;


template <class D> void BM_DictionaryInsertRand(benchmark::State& state) {
  D* d = new D;
  for (auto _ : state) {
    state.PauseTiming();
    for (int j = 0; j < state.range(0); ++j) {
      d->insert(rand(), 0);
    }
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j) {
      d->insert(rand(), 0);
    }
    state.SetItemsProcessed(state.iterations() * state.range(1));
  }
  delete d;
}

template <class D> void BM_DictionaryInsertRand_with_args(benchmark::State& state) {
  D* d = new D(state.range(0), 1. / float(state.range(1)));
  for (auto _ : state) {
    state.PauseTiming();
    for (int j = 0; j < state.range(2); ++j) {
      d->insert(rand(), 0);
    }
    state.ResumeTiming();
    for (int j = 0; j < state.range(3); ++j) {
      d->insert(rand(), 0);
    }
    state.SetItemsProcessed(state.iterations() * state.range(3));
  }
  delete d;
}

//BENCHMARK(BM_DictionaryInsertRand, ZipTree)->RangeMultiplier(2)->Ranges({{1<<8, 8<<8}, {128, 512}});
//
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, ZipTree)->RangeMultiplier(2)->Ranges({{1<<8, 1<<8}, {128, 128}});
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, Treap)->RangeMultiplier(2)->Ranges({{1<<8, 1<<8}, {128, 128}});
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand_with_args, SkipList)
        ->RangeMultiplier(2)
        ->Args({16, 2, 512, 128});

BENCHMARK_MAIN();
