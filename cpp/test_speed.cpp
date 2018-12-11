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
#include <utility>
#include <random>
#include <assert.h>

using namespace std;


int seed;

typedef Dictionary D;

void test_uniform_access_varying_initial_size(vector<pair<D*, string>>* dicts) {
    int instance_size_min = 16;
    int instance_size_max = 1<<20;
    int num_accesses = 1024;
    int min_iters = 10;
    int max_iters = 5000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;

    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());

    uniform_int_distribution<int> distribution;

    ofstream out;
    out.open("uniformAccessVaryingInitialSize.csv");
    out << "data_structure,test_name,instance_size,num_accesses,time_micro_seconds\n";

    Timer timer;

    //for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
    for (int instance_size = instance_size_max; instance_size >= instance_size_min; instance_size /= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            // Prepare key_list
            vector<int> key_list;
            for (int i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);

            vector<int> key_accessed;
            distribution = uniform_int_distribution<int>(0, key_list.size() -1); // unform distribution 0 <= x <= size -1
            for (int i = 0; i < num_accesses; i ++) {
                key_accessed.push_back(distribution(rng));
            }

            // For each iteration, for each key list, perform the same test
            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                string ds_name = dict->second;
                D* s = dict->first;

                // Set Up
                for (auto it = key_list.begin(); it!=key_list.end(); it++) {
                    s->emplace(*it, 0);
                }

                out << ds_name << ",uniformAccessVaryingInitialSize,"  << instance_size <<  "," << num_accesses << ",";

                timer.start();
                // Actual test
                for (auto it = key_accessed.begin(); it != key_accessed.end(); it++) {
                    assert(s->contains(*it));
                }
                timer.pause();
                out << timer.get_runtime() << "\n";

                // Tear Down
                timer.reset();
                s->clear();
            }

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                cout << "\t" << iter << "\n";
                break;
            }
        }
    }
    out.close();
}

int main(int argc, char** argv) {
    if (argc > 1) {
        seed = atoi(argv[1]);
    } else {
        seed = time(0);
    }
    cout << "seed: " << seed << endl;
    srand(seed);

    //test_insert_from_list();
    //test_insert_from_rand_list();
    //test_uniform_access_fixed_start();
    //test_zipf_access_fixed_start();
    //test_zipf_more_accesses();
    //test_insert_from_scratch();

    vector<pair<D*, string>> dicts;
    dicts.push_back(make_pair(new ZipTree, "ZipTree"));
    dicts.push_back(make_pair(new SkipList(16, 0.5), "SkipList"));
    dicts.push_back(make_pair(new Treap, "Treap"));
    dicts.push_back(make_pair(new SplayTree, "SplayTree"));
    dicts.push_back(make_pair(new RedBlack, "RedBlack"));

    test_uniform_access_varying_initial_size(&dicts);
    return 0;
}
