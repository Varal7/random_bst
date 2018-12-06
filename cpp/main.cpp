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
    Dictionary *t, *s;
    Dictionary *z_vanilla, *z_update;
    DictCorrectnessTest *dct = new DictCorrectnessTest(100);
    printf("Zip tree correctness...\n ");
    printf("z_update\n");
    z_update = new ZipTree(0.5, true);
    dct->set_up(z_update); dct->run();
    printf("z_vanilla\n");
    z_vanilla = new ZipTree(0.5, false);
    dct->set_up(z_vanilla); dct->run();

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
