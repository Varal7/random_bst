#include <hayai/hayai.hpp>
#include "dict_speed_test.h"
#include <assert.h>

using namespace std;

void test_speed_naive(Dictionary*& d) {
    std::vector<int> list;
    for (int i = 0; i < 20000; i++) {
        list.push_back(i);
    }

    std::random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->insert(*it, 0);
    }

    std::random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        assert(d->contains(*it));
    }

    std::random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->remove(*it);
        assert(!(d->contains(*it)));
    }
}


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
