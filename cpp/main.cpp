#include <iostream>
#include <cstdlib>
#include <vector>
#include <assert.h>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "timer.h"

using namespace std;

void test_skip_list() {
  /*
  A very primitive test suite for the SkipList class. To compile, run
  $ g++ SkipList_test.cpp SkipList.cpp
  */
  SkipNode *n = new SkipNode(1, 10, 4);
  std::cout << "SkipNode level is " << n->level << ".\n";

  SkipList *list = new SkipList(16, 0.5);
  std::cout << "INT_MIN is " << INT_MAX << ".\n";


  //std::cout << list->header_->value << std::endl;
  //std::cout << list->header_->key << std::endl;
  SkipNode* nil_ptr = list->search(INT_MAX);

  if (nil_ptr == nullptr)
    std::cout << "Pointer is null." << std::endl;
  else
    std::cout << "Header value is " << nil_ptr->value << std::endl;

    //  std::cout << "Here are some random levels: "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << " "
    //  << list->random_level() << ". Does that distribution look right?"
    //  << std::endl;

  list->insert(2, 20);
  list->insert(4, 40);
  list->insert(3, 30);
  list->insert(1, 10);
  list->insert(5, 50);

  std::cout << "Value at key 3 is " << list->search(3)->value << std::endl;
  std::cout << "Value at key 2 is " << list->search(2)->value << std::endl;
  std::cout << "Value at key 4 is " << list->search(4)->value << std::endl;
  std::cout << "Value at key 1 is " << list->search(1)->value << std::endl;
  std::cout << "Value at key 5 is " << list->search(5)->value << std::endl;

  std::cout << "Level at key 3 is " << list->search(3)->level << std::endl;
  std::cout << "Level at key 2 is " << list->search(2)->level << std::endl;
  std::cout << "Level at key 4 is " << list->search(4)->level << std::endl;
  std::cout << "Level at key 1 is " << list->search(1)->level << std::endl;
  std::cout << "Level at key 5 is " << list->search(5)->level << std::endl;

  // Insert some new values
  list->insert(4, 400);
  list->insert(3, 300);
  list->insert(5, 500);
  list->insert(2, 200);
  list->insert(1, 100);

  std::cout << "Ok, now some values have been changed." << std::endl;
  std::cout << "Value at key 1 is " << list->search(1)->value << std::endl;
  std::cout << "Value at key 2 is " << list->search(2)->value << std::endl;
  std::cout << "Value at key 3 is " << list->search(3)->value << std::endl;
  std::cout << "Value at key 4 is " << list->search(4)->value << std::endl;
  std::cout << "Value at key 5 is " << list->search(5)->value << std::endl;

  // Delete some stuff
  list->remove(3);
  std::cout << "Ok, now some stuff has been deleted." << std::endl;
  //std::cout << "Level at key 3 is " << list->search(3)->level << std::endl;
  std::cout << "Level at key 2 is " << list->search(2)->level << std::endl;
  std::cout << "Level at key 4 is " << list->search(4)->level << std::endl;
  std::cout << "Level at key 1 is " << list->search(1)->level << std::endl;
  std::cout << "Level at key 5 is " << list->search(5)->level << std::endl;

  delete n;
  delete list;
}

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
    for (int i = 0; i < 20000; i ++) {
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



int main() {
    srand(time(0));
    uint64 tic, tac;
    Dictionary *z, *t, *s;

    printf("Zip trees\n");
    z = new ZipTree;
    tic = GetTimeMs64();
    test_correctness_dict(z);
    tac = GetTimeMs64();
    printf("time: %d ms\n", tac-tic);

    printf("\nTreaps\n");
    t = new Treap;
    tic = GetTimeMs64();
    test_correctness_dict(t);
    tac = GetTimeMs64();
    printf("time: %d ms\n", tac-tic);

    printf("\nSkip lists\n");
    s = new SkipList(16, 0.5);
    tic = GetTimeMs64();
    test_correctness_dict(s);
    tac = GetTimeMs64();

    printf("\nSpeed test");
    printf("Zip trees\n");
    z = new ZipTree;
    tic = GetTimeMs64();
    test_speed_naive(z);
    tac = GetTimeMs64();
    printf("time: %d ms\n", tac-tic);

    printf("\nTreaps\n");
    t = new Treap;
    tic = GetTimeMs64();
    test_speed_naive(t);
    tac = GetTimeMs64();
    printf("time: %d ms\n", tac-tic);

    printf("\nSkip lists\n");
    s = new SkipList(16, 0.5);
    tic = GetTimeMs64();
    test_speed_naive(s);
    tac = GetTimeMs64();
    printf("time: %d ms\n", tac-tic);


    //test_skip_list();
}
