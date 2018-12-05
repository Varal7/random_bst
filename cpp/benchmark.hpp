#include <hayai/hayai.hpp>
#include "dict_speed_test.h"

using namespace std;

BENCHMARK(ZipTree, SpeedNaive, 10, 10)
{
    Dictionary *d = new ZipTree;
    test_speed_naive(d);
}

BENCHMARK(Treap, SpeedNaive, 10, 10)
{
    Dictionary *d = new Treap;
    test_speed_naive(d);
}

BENCHMARK(SkipList, SpeedNaive, 10, 10)
{
    Dictionary *d = new SkipList(16, 0.5);
    test_speed_naive(d);
}
