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

void test_height(vector<pair<D*, string>>* dicts) {
    int instance_size_min = 16;
    int instance_size_max = 1<<20;
    int min_iters = 50;
    int max_iters = 5000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;


    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());

    uniform_int_distribution<int> distribution;

    ofstream out;
    out.open("heights.csv");
    out << "data_structure,test_name,instance_size,height\n";


    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
    //for (int instance_size = instance_size_max; instance_size >= instance_size_min; instance_size /= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            // Prepare key_list and access_list for all data structures
            vector<int> key_list;
            for (int i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            //shuffle(begin(key_list), end(key_list), rng);

            // For each iteration, for each key list, perform the same test
            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                // Log
                string ds_name = dict->second;
                D* s = dict->first;
                out << ds_name << ",height,"  << instance_size <<  ",";

                // Set Up
                for (auto it = key_list.begin(); it!=key_list.end(); it++) {
                    s->emplace(*it, 0);
                }

                // Actual test
                out << s->height() << "\n";

                // Tear down
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

    vector<pair<D*, string>> dicts;
    dicts.push_back(make_pair(new ZipTree, "ZipTree"));
    dicts.push_back(make_pair(new ZipTree(0.5, false, true), "ZipTreeFloatRank"));
    dicts.push_back(make_pair(new Treap, "Treap"));

    test_height(&dicts);

    dicts.push_back(make_pair(new ZipTree(0.5, true), "ZipTreeSelfAdjust"));


    return 0;
}
