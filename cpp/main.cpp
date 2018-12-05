#include <iostream>
#include <cstdlib>
#include <hayai/hayai.hpp>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "dict_correctness_test.h"
#include "dict_speed_test.h"
#include "benchmark.hpp"

using namespace std;

void test_correctness() {
    Dictionary *z, *t, *s;
    DictCorrectnessTest *dct = new DictCorrectnessTest(20000);
    z = new ZipTree;
    t = new Treap;
    s = new SkipList(16, 0.5);
    printf("Zip tree correctness... ");
    dct->set_up(z); dct->run();
    printf("check\n");
    printf("Treap correctness... ");
    dct->set_up(t); dct->run();
    printf("check\n");
    printf("SkipList correctness... ");
    dct->set_up(s); dct->run();
    printf("check\n");

    delete dct;
    delete z;
    delete t;
    delete s;
}


void test_speed() {
    hayai::ConsoleOutputter consoleOutputter;
    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
}


int main(int argc, char** argv) {
    int x;
    if (argc > 1) {
        x = atoi(argv[1]);
    } else {
        x = time(0);
    }
    cout << "seed: " << x << endl;
    srand(x);

    test_correctness();
    test_speed();

    return 0;
}
