#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "dict_correctness_test.h"
//#include "dict_speed_test.h"
#include "benchmark/benchmark.h"

using namespace std;


template <class D, D*& d> void BM_DictionaryInsertRand(benchmark::State& state) {
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
}

//BENCHMARK(BM_DictionaryInsertRand, ZipTree)->RangeMultiplier(2)->Ranges({{1<<8, 8<<8}, {128, 512}});
//
ZipTree* z = new ZipTree;
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, ZipTree, z)->RangeMultiplier(2)->Ranges({{1<<8, 1<<8}, {128, 128}});

Treap* t = new Treap;
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, Treap, t)->RangeMultiplier(2)->Ranges({{1<<8, 1<<8}, {128, 128}});

SkipList* s = new SkipList(16, 0.5);
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SkipList, s)->RangeMultiplier(2)->Ranges({{1<<8, 1<<8}, {128, 128}});

BENCHMARK_MAIN();
