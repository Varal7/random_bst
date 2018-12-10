#include <iostream>
#include <fstream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "splay_tree.h"
#include "red_black.h"
#include "splay_tree_logged.h"
#include "dict_speed_test.h"
#include "timer.h"
#include <map>
#include <random>

using namespace std;


typedef Dictionary D;

void test_insert_from_list() {
    uint32 instance_size_min = 16;
    uint32 instance_size_max = 1<<20;
    int max_iters = 5;

    for (uint32 instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        for (int iter = 0; iter < max_iters; iter++) {
            vector<uint32> key_list;
            for (uint32 i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            TestInsertFromList *dst = new TestInsertFromList(&key_list);

            Dictionary *s;

            printf("SkipList insertFromList %lu ", instance_size);
            s = new SkipList(16, 0.5); dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("ZipTree insertFromList %lu ", instance_size);
            s = new ZipTree; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("Treap insertFromList %lu ", instance_size);
            s = new Treap; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("SplayTree insertFromList %lu ", instance_size);
            s = new SplayTree; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("RedBlack insertFromList %lu ", instance_size);
            s = new RedBlack; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;
        }
    }
}

void test_insert_from_rand_list() {
    uint32 instance_size_min = 16;
    uint32 instance_size_max = 1<<20;
    int max_iters = 5;

    for (uint32 instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        for (int iter = 0; iter < max_iters; iter++) {
            TestInsertFromRandList *dst = new TestInsertFromRandList(instance_size);

            Dictionary *s;

            printf("SkipList insertFromRandList %lu ", instance_size);
            s = new SkipList(16, 0.5); dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("ZipTree insertFromRandList %lu ", instance_size);
            s = new ZipTree; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("Treap insertFromRandList %lu ", instance_size);
            s = new Treap; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("SplayTree insertFromRandList %lu ", instance_size);
            s = new SplayTree; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;

            printf("RedBlack insertFromRandList %lu ", instance_size);
            s = new RedBlack; dst->set_up(s); dst->run(); cout << dst->get_runtime() << "\n";
            delete s;
        }
    }
}


void test_uniform_access_fixed_start() {
    int instance_size_min = 16;
    //int instance_size_max = 16;;
    int instance_size_max = 1<<20;
    int num_accesses = 1024;
    int min_iters = 10;
    int max_iters = 5000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;

    uint64 start;
    auto rng = std::default_random_engine {};

    ofstream out;
    out.open("uniformAccesFixedStart.csv");
    out << "data_structure,test_name,instance_size,num_accesses,time_micro_seconds\n";

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            vector<int> key_list;
            for (int i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);
            TestUniformAccessFixedStart *dst = new TestUniformAccessFixedStart(&key_list, num_accesses);

            Dictionary *s;

            out << "SkipList,uniformAccessFixedStart,"  << instance_size <<  "," << num_accesses << ",";
            s = new SkipList(16, 0.5); dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "ZipTree,uniformAccessFixedStart,"  << instance_size <<  "," << num_accesses << ",";;
            s = new ZipTree; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "Treap,uniformAccessFixedStart,"  << instance_size <<  "," << num_accesses << ",";;
            s = new Treap; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "SplayTree,uniformAccessFixedStart,"  << instance_size <<  "," << num_accesses << ",";;
            s = new SplayTree; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "RedBlack,uniformAccessFixedStart,"  << instance_size <<  "," << num_accesses << ",";;
            s = new RedBlack; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                break;
            }
        }
    }
    out.close();
}



void test_zipf_access_fixed_start() {
    double alpha = 0.5;
    int instance_size_min = 16;
    int instance_size_max = 1<<20;
    int num_accesses = 1024;
    int min_iters = 10;
    int max_iters = 5000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;

    uint64 start;
    auto rng = std::default_random_engine {};

    ofstream out;
    out.open("zipfAccesFixedStart.csv");
    out << "data_structure,test_name,instance_size,num_accesses,alpha,time_micro_seconds\n";

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            vector<int> key_list;
            for (int i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);
            TestZipfAccessFixedStart *dst = new TestZipfAccessFixedStart(&key_list, num_accesses, alpha);

            Dictionary *s;

            out << "SkipList,zipfAccessFixedStart,"  << instance_size <<  "," << num_accesses << "," << alpha << ",";
            s = new SkipList(16, 0.5); dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "ZipTree,zipfAccessFixedStart,"  << instance_size <<  "," << num_accesses << "," << alpha << ",";
            s = new ZipTree; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "Treap,zipfAccessFixedStart,"  << instance_size <<  "," << num_accesses << "," << alpha << ",";
            s = new Treap; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "SplayTree,zipfAccessFixedStart,"  << instance_size <<  "," << num_accesses << "," << alpha << ",";
            s = new SplayTree; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            out << "RedBlack,zipfAccessFixedStart,"  << instance_size <<  "," << num_accesses << "," << alpha << ",";
            s = new RedBlack; dst->set_up(s); dst->run();
            out << dst->get_runtime() << "\n";
            delete s;

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                break;
            }
        }
    }
    out.close();
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

    //test_insert_from_list();
    //test_insert_from_rand_list();
    test_uniform_access_fixed_start();
    test_zipf_access_fixed_start();
    return 0;
}
