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


int instance_size_min = 1<<18;
int instance_size_max = 1<<18;
int min_iters = 300;
int max_iters = 300;
int num_accesses = 1<<14;
int num_inserts = 1<<14;
int num_deletes = 1<<14;

int seed;

typedef Dictionary D;

void test_change_subset(vector<pair<D*, string>>* dicts) {
    int instance_size = 1<<20;
    int num_elements_per_bucket = 1024;
    int num_measures_per_epochs = 1024;
    int num_accesses_per_measures = 1<<15;
    int num_epochs = 20;

    int min_iters = 1000;
    int max_iters = 1000;

    int max_micro_sec = 1000 * 1000 * 3 * 1;
    uint64 start;

    std::random_device rng;
    std::mt19937 urng(rng());

    uniform_int_distribution<int> distribution;

    ofstream out;
    out.open("accessSubset.csv");
    out << "data_structure,test_name,instance_size,num_elements_per_bucket,num_accesses_per_measures,measure_id,time_micro_seconds\n";

    Timer timer;

    for (int iter = 0; iter < max_iters; iter++) {
        start = GetTimeMicroS64();
        cout << iter << "\n";
        // Prepare key_list and access_list for all data structures
        vector<int> key_list;
        cout << iter << "\n";
        for (int i = 0; i < instance_size; i ++) {
            key_list.push_back(i);
        }
        shuffle(begin(key_list), end(key_list), rng);
        vector<int> key_accessed = key_list;
        shuffle(begin(key_accessed), end(key_accessed), rng);

        distribution = uniform_int_distribution<int>(0, num_elements_per_bucket - 1); // unform distribution 0 <= x <= #el -1

        for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
            string ds_name = dict->second;
            D* s = dict->first;
            timer.start();
            timer.pause();
            int offset = 0;
            int measure_id = 0;
            for (int epoch_id = 0; epoch_id < num_epochs; epoch_id++) {
                for (int measure_in_epoch = 0; measure_in_epoch < num_measures_per_epochs; measure_in_epoch += 1) {

                    cout << measure_id << endl;
                    // Log
                    out << ds_name << ",accessSubset,"  << instance_size <<  "," << num_elements_per_bucket <<  "," << num_accesses_per_measures << "," << measure_id << ",";

                    timer.resume();
                    // Actual test
                    for (int i = 0; i < num_accesses_per_measures; i++) {
                        assert(s->contains(key_accessed[offset + distribution(rng)]));
                    }
                    timer.pause(); out << timer.get_runtime() << "\n";
                    measure_id ++;
                }
            offset += num_elements_per_bucket;
            }
        // Tear Down
            timer.reset(); s->clear();
        }
        if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
            cout << "\t" << iter << "\n";
            break;
        }
    }
    out.close();
}



void test_subset(vector<pair<D*, string>>* dicts) {
    int instance_size = 1<<20;
    int num_elements_per_bucket = 1024;
    int num_measures = 1024;
    int num_accesses_per_measures = 1<<15;

    int min_iters = 1000;
    int max_iters = 1000;

    int max_micro_sec = 1000 * 1000 * 3 * 1;
    uint64 start;

    std::random_device rng;
    std::mt19937 urng(rng());

    uniform_int_distribution<int> distribution;

    ofstream out;
    out.open("accessSubset.csv");
    out << "data_structure,test_name,instance_size,num_elements_per_bucket,num_accesses_per_measures,measure_id,time_micro_seconds\n";

    Timer timer;

    for (int iter = 0; iter < max_iters; iter++) {
        start = GetTimeMicroS64();
        cout << iter << "\n";
        // Prepare key_list and access_list for all data structures
        vector<int> key_list;
        cout << iter << "\n";
        for (int i = 0; i < instance_size; i ++) {
            key_list.push_back(i);
        }
        shuffle(begin(key_list), end(key_list), rng);
        vector<int> key_accessed = key_list;
        shuffle(begin(key_accessed), end(key_accessed), rng);

        distribution = uniform_int_distribution<int>(0, num_elements_per_bucket - 1); // unform distribution 0 <= x <= #el -1

        for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
            timer.start();
            timer.pause();
            int offset = 0;
            string ds_name = dict->second;
            D* s = dict->first;
            for (int measure_id = 0; measure_id < num_measures; measure_id += 1) {

                cout << measure_id << endl;
                // Log
                out << ds_name << ",accessSubset,"  << instance_size <<  "," << num_elements_per_bucket <<  "," << num_accesses_per_measures << "," << measure_id << ",";

                timer.resume();
                // Actual test
                for (int i = 0; i < num_accesses_per_measures; i++) {
                    assert(s->contains(key_accessed[offset + distribution(rng)]));
                }
                timer.pause(); out << timer.get_runtime() << "\n";
            }
            // Tear Down
            timer.reset(); s->clear();
        }
        if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
            cout << "\t" << iter << "\n";
            break;
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
    dicts.push_back(make_pair(new ZipTree(0.5, false), "ZipTree"));
    dicts.push_back(make_pair(new ZipTree(0.5, true), "ZipTreeSelfAdjust"));
    dicts.push_back(make_pair(new SkipList(16, 0.5), "SkipList"));
    dicts.push_back(make_pair(new Treap, "Treap"));
    dicts.push_back(make_pair(new SplayTree, "SplayTree"));
    dicts.push_back(make_pair(new RedBlack, "RedBlack"));


    test_subset(&dicts);
    test_change_subset(&dicts);


    return 0;
}
