#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "splay_tree.h"
#include "red_black.h"
#include "splay_tree_logged.h"
#include "skip_list_logged.h"
#include "zip_trees_logged.h"
#include "treaps_logged.h"
#include "dict_log_test.h"

using namespace std;

void print_status(DictLogTest *dct) {
  if (dct->get_status() == TEST_PASS_) {
    cout << "TEST PASS" << endl;
  } else {
    cout << "TEST FAIL" << endl;
  }
}


void test_correctness() {
    Dictionary *t, *s;
    Dictionary *z_vanilla, *z_update;
    Dictionary *sp;
    Dictionary *rb;
    DictLogTest *dct = new DictLogTest(1000);

    printf("Splay tree correctness... ");
    sp = new SplayTreeLogged();
    dct->set_up(sp); dct->run();
    print_status(dct);

    printf("SkipList correctness... ");
    s = new SkipListLogged(16, 0.5);
    dct->set_up(s); dct->run();
    print_status(dct);

    printf("Zip tree correctness...\n");
    printf("z_vanilla\n");
    z_vanilla = new ZipTreeLogged(0.5, false, false);
    dct->set_up(z_vanilla); dct->run();
    printf("z_update\n");
    z_update = new ZipTreeLogged(0.5, true, false);
    dct->set_up(z_update); dct->run();
    printf("z_vanilla_frac\n");
    z_vanilla = new ZipTreeLogged(0.5, false, true);
    dct->set_up(z_vanilla); dct->run();
    printf("z_update_frac\n");
    z_update = new ZipTreeLogged(0.5, true, true);
    dct->set_up(z_update); dct->run();
    print_status(dct);

    printf("Treap correctness... ");
    t = new TreapLogged;
    dct->set_up(t); dct->run();
    print_status(dct);

    printf("Red black correctness... ");
    rb = new RedBlack;
    dct->set_up(rb); dct->run();
    print_status(dct);

    delete dct;
    delete t;
    delete s;
    delete sp;
    delete rb;
}


int main(int argc, char** argv) {
    int x;
    if (argc > 1) {
        x = atoi(argv[1]);
    } else {
        x = time(0);
    }
    srand(x);

    std::cout << std::endl;
    cout << "seed: " << x << endl;
    std::cout << "-------------------------------------------------" << std::endl;

    test_correctness();
    //test_speed();
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Maximum memory used by splay tree is " << SplayTreeLogged::log_->greatest_size() << " bytes." << std::endl;
    std::cout << "Maximum depth of splay tree is " << SplayTreeLogged::log_->greatest_depth() << "." << std::endl;
    std::cout << std::endl;
    std::cout << "Maximum memory used by skip list is " << SkipListLogged::log_->greatest_size() << " bytes." << std::endl;
    std::cout << std::endl;
    std::cout << "Maximum memory used by zip tree is " << ZipTreeLogged::log_->greatest_size() << " bytes." << std::endl;
    std::cout << "Maximum depth of zip tree is " << ZipTreeLogged::log_->greatest_depth() << "." << std::endl;
    std::cout << std::endl;
    std::cout << "Maximum memory used by treap is " << TreapLogged::log_->greatest_size() << " bytes." << std::endl;
    std::cout << "Maximum depth of treap is " << TreapLogged::log_->greatest_depth() << "." << std::endl;
    return 0;
}
