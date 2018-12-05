#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "dict_correctness_test.h"
//#include "dict_speed_test.h"
#include "benchmark/benchmark.h"

using namespace std;

static void BM_StringCreation(benchmark::State& state) {
for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
std::string x = "hello";
for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
