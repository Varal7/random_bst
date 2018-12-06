#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "splay_tree.h"
#include "dict_correctness_test.h"
//#include "dict_speed_test.h"
#include "benchmark/benchmark.h"

using namespace std;


template <class D> void BM_DictionaryInsertRand(benchmark::State& state) {
  for (auto _ : state) {
    D* d = new D;
    state.PauseTiming();

    for (int j = 0; j < state.range(0); ++j) {
      d->emplace(rand(), 0);
    }
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j) {
      d->emplace(rand(), 0);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * state.range(1));
}

template <class D> void BM_DictionaryAccessAll(benchmark::State& state) {
  int num_elements = state.range(0);
  int num_accesses = state.range(1);
  assert(num_accesses < num_elements);

  // For all instances initialize elements
  vector<int> elements(num_elements);
  for (int j=0; j < num_elements; ++j) {
      elements[j] = j;
  }

  for (auto _ : state) {
    D* d = new D;
    // Before the test shuffle the elements and place them in the dict
    state.PauseTiming();
    random_shuffle(elements.begin(), elements.end());
    for (int j = 0; j < num_elements; ++j) {
      d->emplace(elements[j], 0);
    }
    random_shuffle(elements.begin(), elements.end());
    state.ResumeTiming();

    // Time num_acesses accesses
    for (int j = 0; j < num_accesses; ++j) {
      d->emplace(elements[j], 0);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_accesses);
}


//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

BENCHMARK_TEMPLATE(BM_DictionaryAccessAll, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
BENCHMARK_TEMPLATE(BM_DictionaryAccessAll, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
BENCHMARK_TEMPLATE(BM_DictionaryAccessAll, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
BENCHMARK_TEMPLATE(BM_DictionaryAccessAll, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
BENCHMARK_TEMPLATE(BM_DictionaryAccessAll, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

BENCHMARK_MAIN();
