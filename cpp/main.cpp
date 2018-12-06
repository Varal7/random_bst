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
    DictCorrectnessTest *dct = new DictCorrectnessTest(100);
    printf("Zip tree correctness... ");
    //ztt = new ZipTree(0.5, true, true);
    //dct->set_up(ztt); dct->run();
    //zft = new ZipTree(0.5, false, true);
    //dct->set_up(zft); dct->run();
    //
    printf("\nfalse false\n");
    zff = new ZipTree(0.5, false, false);
    dct->set_up(zff); dct->run();
    printf("\ntrue false\n");
    ztf = new ZipTree(0.5, true, false);
    dct->set_up(ztf); dct->run();

    printf("check\n");
    printf("Treap correctness... ");
    t = new Treap;
    dct->set_up(t); dct->run();
    printf("check\n");
    printf("SkipList correctness... ");
    s = new SkipList(16, 0.5);
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
