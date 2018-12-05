#include "test.h"

#ifndef DICT_SPEED_TEST_H_
#define DICT_SPEED_TEST_H_

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

#endif
