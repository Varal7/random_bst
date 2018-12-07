#include <iostream>
#include <cstdlib>
#include <hayai/hayai.hpp>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "splay_tree.h"
#include "splay_tree_logged.h"
#include "dict_correctness_test.h"
#include "dict_speed_test.h"
#include "genzipf.h"

using namespace std;

void print_status(DictCorrectnessTest *dct) {
  if (dct->get_status() == TEST_PASS_) {
    cout << "TEST PASS" << endl;
  } else {
    cout << "TEST FAIL" << endl;
  }
}

void test_correctness() {
    Dictionary *t, *s;
    Dictionary *z_vanilla, *z_update;
    Dictionary *sp_l;
    DictCorrectnessTest *dct = new DictCorrectnessTest(2000);
    printf("Zip tree correctness...\n");
    printf("z_vanilla\n");
    z_vanilla = new ZipTree(0.5, false, false);
    dct->set_up(z_vanilla); dct->run();
    printf("z_update\n");
    z_update = new ZipTree(0.5, true, false);
    dct->set_up(z_update); dct->run();
    printf("z_vanilla_frac\n");
    z_vanilla = new ZipTree(0.5, false, true);
    dct->set_up(z_vanilla); dct->run();
    printf("z_update_frac\n");
    z_update = new ZipTree(0.5, true, true);
    dct->set_up(z_update); dct->run();
    print_status(dct);

    printf("Treap correctness... ");
    t = new Treap;
    dct->set_up(t); dct->run();
    print_status(dct);
    printf("SkipList correctness... ");
    s = new SkipList(16, 0.5);
    dct->set_up(s); dct->run();
    print_status(dct);

    printf("Splay tree correctness... ");
    sp_l = new SplayTreeLogged();
    dct->set_up(s); dct->run();
    print_status(dct);

    delete dct;
    delete t;
    delete s;
    delete sp_l;
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
    //test_speed();
    std::cout << "Maximum memory used by splay tree is " << SplayTreeLogged::log_->greatest_size() << " bytes." << std::endl;
    return 0;
}
