#include <iostream>
#include <cstdlib>
#include <hayai/hayai.hpp>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "dict_correctness_test.h"
#include "dict_speed_test.h"

using namespace std;

void test_correctness() {
    Dictionary *ztt, *zft, *ztf, *zff, *t, *s;
    DictCorrectnessTest *dct = new DictCorrectnessTest(20000);
    ztt = new ZipTree(0.5, true, true);
    zft = new ZipTree(0.5, false, true);
    ztf = new ZipTree(0.5, true, false);
    zff = new ZipTree(0.5, false, false);
    t = new Treap;
    s = new SkipList(16, 0.5);
    printf("Zip tree correctness... ");
    dct->set_up(zff); dct->run();
    dct->set_up(zft); dct->run();
    dct->set_up(ztf); dct->run();
    dct->set_up(zff); dct->run();
    printf("check\n");
    printf("Treap correctness... ");
    dct->set_up(t); dct->run();
    printf("check\n");
    printf("SkipList correctness... ");
    dct->set_up(s); dct->run();
    printf("check\n");

    delete dct;
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
