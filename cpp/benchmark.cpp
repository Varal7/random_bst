#include <iostream>
#include <cstdlib>
#include <random>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "splay_tree.h"
#include "benchmark/benchmark.h"
#include "genzipf.h"

using namespace std;

// Set up pseudorandom number generator
auto rng = std::default_random_engine {};


template <class D> void BM_DictionaryInsertRand(benchmark::State& state) {
  int num_elements = state.range(0);
  int num_inserts = state.range(1);
  for (auto _ : state) {
    D* d = new D;
    state.PauseTiming();

    for (int j = 0; j < num_elements; ++j) {
      d->emplace(rand(), 0);
    }
    state.ResumeTiming();

    for (int j = 0; j < num_inserts; ++j) {
      d->emplace(rand(), 0);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_inserts);
}

template <class D> void BM_DictionaryAccess(benchmark::State& state) {
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
    shuffle(begin(elements), end(elements), rng);
    for (int j = 0; j < num_elements; ++j) {
      d->emplace(elements[j], 0);
    }
    shuffle(begin(elements), end(elements), rng);
    state.ResumeTiming();

    // Time num_acesses accesses
    for (int j = 0; j < num_accesses; ++j) {
      d->find(elements[j]);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_accesses);
}


template <class D> void BM_DictionaryRemoves(benchmark::State& state) {
  int num_elements = state.range(0);
  int num_deletes = state.range(1);
  assert(num_deletes < num_elements);

  // For all instances initialize elements
  vector<int> elements(num_elements);
  for (int j=0; j < num_elements; ++j) {
      elements[j] = j;
  }

  for (auto _ : state) {
    D* d = new D;
    // Before the test shuffle the elements and place them in the dict
    state.PauseTiming();
    shuffle(begin(elements), end(elements), rng);
    for (int j = 0; j < num_elements; ++j) {
      d->emplace(elements[j], 0);
    }
    shuffle(begin(elements), end(elements), rng);
    state.ResumeTiming();

    // Time num_deletes deletes
    for (int j = 0; j < num_deletes; ++j) {
      d->erase(elements[j]);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_deletes);
}

template <class D> void BM_DictionaryInsertOrdered(benchmark::State& state) {
  int num_elements = state.range(0);
  int num_inserts = state.range(1);

  // For all instances initialize elements
  vector<int> elements(num_elements);
  for (int j=0; j < num_elements; ++j) {
      elements[j] = j;
  }

  for (auto _ : state) {
    D* d = new D;
    // Before the test shuffle the elements and place them in the dict
    state.PauseTiming();
    shuffle(begin(elements), end(elements), rng);
    for (int j = 0; j < num_elements; ++j) {
      d->emplace(elements[j], 0);
    }
    state.ResumeTiming();

    // Time num_acesses accesses
    for (int j = num_elements; j < num_elements + num_inserts; ++j) {
      d->emplace(j, 0);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_inserts);
}



template <class D> void BM_DictionaryAccessOrdered(benchmark::State& state) {
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
    shuffle(begin(elements), end(elements), rng);
    for (int j = 0; j < num_elements; ++j) {
      d->emplace(elements[j], 0);
    }
    state.ResumeTiming();

    // Time num_acesses accesses
    for (int j = 0; j < num_accesses; ++j) {
      d->find(j);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_accesses);
}


template <class D> void BM_DictionaryRemovesOrdered(benchmark::State& state) {
  int num_elements = state.range(0);
  int num_deletes = state.range(1);
  assert(num_deletes < num_elements);

  // For all instances initialize elements
  vector<int> elements(num_elements);
  for (int j=0; j < num_elements; ++j) {
      elements[j] = j;
  }

  for (auto _ : state) {
    D* d = new D;
    // Before the test shuffle the elements and place them in the dict
    state.PauseTiming();
    shuffle(begin(elements), end(elements), rng);
    for (int j = 0; j < num_elements; ++j) {
      d->emplace(elements[j], 0);
    }
    shuffle(begin(elements), end(elements), rng);
    state.ResumeTiming();

    // Time num_deletes deletes
    for (int j = 0; j < num_deletes; ++j) {
      d->erase(j);
    }
    delete d;
  }
  state.SetItemsProcessed(state.iterations() * num_deletes);
}

BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, ZipTree)->RangeMultiplier(2)->Ranges({{0, 0}, {1, 1<<20}});
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, Treap)->RangeMultiplier(2)->Ranges({{0, 0}, {1, 1<<20}});
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SplayTree)->RangeMultiplier(2)->Ranges({{0, 0}, {1, 1<<20}});
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SkipList)->RangeMultiplier(2)->Ranges({{0, 0}, {1, 1<<20}});
BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, map<int, int>)->RangeMultiplier(2)->Ranges({{0, 0}, {1, 1<<20}});

//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertRand, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

//BENCHMARK_TEMPLATE(BM_DictionaryAccess, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccess, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccess, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccess, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccess, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

//BENCHMARK_TEMPLATE(BM_DictionaryRemoves, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemoves, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemoves, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemoves, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemoves, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

//BENCHMARK_TEMPLATE(BM_DictionaryInsertOrdered, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertOrdered, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertOrdered, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertOrdered, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryInsertOrdered, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

//BENCHMARK_TEMPLATE(BM_DictionaryAccessOrdered, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccessOrdered, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccessOrdered, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccessOrdered, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryAccessOrdered, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

//BENCHMARK_TEMPLATE(BM_DictionaryRemovesOrdered, ZipTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemovesOrdered, Treap)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemovesOrdered, SplayTree)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemovesOrdered, SkipList)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});
//BENCHMARK_TEMPLATE(BM_DictionaryRemovesOrdered, map<int, int>)->RangeMultiplier(2)->Ranges({{1<<10, 1<<10}, {128, 128}});

BENCHMARK_MAIN();
