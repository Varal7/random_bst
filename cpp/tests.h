#include <iostream>
#include <cstdlib>
#include <vector>
#include <assert.h>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "timer.h"

#ifndef TESTS_H_
#define TESTS_H_

using namespace std;

void test_correctness_dict(Dictionary*& d) {
    vector<int> list;
    for (int i = 0; i < 10000; i ++) {
        list.push_back(i);
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->insert(*it, 0);
        d->check();
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        assert(d->contains(*it));
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->remove(*it);
        d->check();
        assert(!(d->contains(*it)));
    }
    printf("Correctness test passed\n");

}

void test_speed_naive(Dictionary*& d) {
    vector<int> list;
    for (int i = 0; i < 20000; i++) {
        list.push_back(i);
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->insert(*it, 0);
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        assert(d->contains(*it));
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->remove(*it);
        assert(!(d->contains(*it)));
    }
}


void test_correctness() {
    Dictionary *z, *t, *s;

    printf("Zip trees\n");
    z = new ZipTree;
    test_correctness_dict(z);
    delete z;

    printf("\nTreaps\n");
    t = new Treap;
    test_correctness_dict(t);
    delete t;

    printf("\nSkip lists\n");
    s = new SkipList(16, 0.5);
    test_correctness_dict(s);
    delete s;

}

void test_speed() {
    uint64 tic, tac;
    Dictionary *z, *t, *s;

    printf("\nSpeed test");
    printf("\nZip trees\n");
    z = new ZipTree;
    tic = GetTimeMs64();
    test_speed_naive(z);
    tac = GetTimeMs64();
    printf("time: %d ms\n", int (tac-tic));
    delete z;

    printf("\nTreaps\n");
    t = new Treap;
    tic = GetTimeMs64();
    test_speed_naive(t);
    tac = GetTimeMs64();
    printf("time: %d ms\n", int (tac-tic));
    delete t;

    printf("\nSkip lists\n");
    s = new SkipList(16, 0.5);
    tic = GetTimeMs64();
    test_speed_naive(s);
    tac = GetTimeMs64();
    printf("time: %d ms\n", int (tac-tic));
    delete s;
}

#endif
