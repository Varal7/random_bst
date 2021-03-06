#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
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

const int SORTED = 0;
const int REVERSED = 1;
const int SHUFFLED = 2;

int instance_size_min = 16;
int instance_size_max = 1<<20;
int min_iters = 10;
int max_iters = 1000;
int num_accesses = 1<<22;
int num_inserts = 1024;
int num_deletes = 1024;

int seed;

typedef Dictionary D;

void test_uniform_access_varying_initial_size(vector<pair<D*, string>>* dicts) {
    //int instance_size_min = 16;
    //int num_accesses = 1024;
    //int instance_size_min = 1<<18;
    //int instance_size_max = 1<<18;
    //int num_accesses = 1<<14;
    //int min_iters = 1000;
    //int max_iters = 1000;
    int max_micro_sec = 1000 * 1000 * 30 * 1;

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
            // Prepare key_list and access_list for all data structures
            vector<int> key_list;
            cout << iter << "\n";
            for (int i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);

            vector<int> key_accessed;
            distribution = uniform_int_distribution<int>(0, key_list.size() -1); // unform distribution 0 <= x <= size -1
            for (int i = 0; i < num_accesses; i ++) {
                key_accessed.push_back(key_list[distribution(rng)]);
            }

            // For each iteration, for each key list, perform the same test
            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                // Log
                string ds_name = dict->second;
                D* s = dict->first;
                out << ds_name << ",uniformAccessVaryingInitialSize,"  << instance_size <<  "," << num_accesses << ",";

                // Set Up
                for (auto it = key_list.begin(); it!=key_list.end(); it++) {
                    s->emplace(*it, 0);
                }
                timer.start();

                // Actual test
                for (auto it = key_accessed.begin(); it != key_accessed.end(); it++) {
                    assert(s->contains(*it));
                }
                timer.pause(); out << timer.get_runtime() << "\n";

                // Tear Down
                timer.reset(); s->clear();
            }

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                cout << "\t" << iter << "\n";
                break;
            }
        }
    }
    out.close();
}


void test_zipf_access_varying_initial_size(vector<pair<D*, string>>* dicts, double alpha) {
    //int instance_size_min = 16;
    //int num_accesses = 1024;
    //int instance_size_max = 1<<18;
    //int instance_size_min = 1<<18;
    //int num_accesses = 1<<14;
    //int min_iters = 1000;
    //int max_iters = 1000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;

    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());


    ofstream out;
    out.open("zipfAccessVaryingInitialSize" + to_string(alpha) + ".csv");
    out << "data_structure,test_name,instance_size,num_accesses,alpha,time_micro_seconds\n";

    Timer timer;

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            // Prepare key_list and access_list for all data structures
            vector<int> key_list;
            cout << iter << "\n";
            for (int i = 0; i < instance_size; i ++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);

            vector<int> key_accessed;
            GenZipf genzipf = GenZipf(alpha, key_list.size()); // zipf from 1 to size

            for (int i = 0; i < num_accesses; i ++) {
                key_accessed.push_back(key_list[genzipf.get() - 1]);
            }

            // For each iteration, for each key list, perform the same test
            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                // Log
                string ds_name = dict->second;
                D* s = dict->first;
                out << ds_name << ",zipfAccessVaryingInitialSize,"  << instance_size <<  "," << num_accesses << "," << alpha << ",";

                // Set Up
                for (auto it = key_list.begin(); it!=key_list.end(); it++) {
                    s->emplace(*it, 0);
                }
                timer.start();

                // Actual test
                for (auto it = key_accessed.begin(); it != key_accessed.end(); it++) {
                    assert(s->contains(*it));
                }
                timer.pause(); out << timer.get_runtime() << "\n";

                // Tear Down
                timer.reset(); s->clear();
            }

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                cout << "\t" << iter << "\n";
                break;
            }
        }
    }
    out.close();
}


void test_zipf_varying_number_accesses_fixed_initial_size(vector<pair<D*, string>>* dicts) {
    //int instance_size_min = 16;
    //int instance_size_max = 1<<18;
    int initial_size = 1024;
    //int min_iters = 10;
    //int max_iters = 5000;
    double alpha = 0.99;
    int max_micro_sec = 1000 * 1000 * 60 * 10;

    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());


    ofstream out;
    out.open("zipfVaryingNumberAccessesFixedInitialSize.csv");
    out << "data_structure,test_name,instance_size,initial_size,alpha,time_micro_seconds\n";

    Timer timer;

    start = GetTimeMicroS64();
    for (int iter = 0; iter < max_iters; iter++) {
        cout << iter << "\n";
        // Prepare key_list and access_list for all data structures
        vector<int> key_list;
        for (int i = 0; i < initial_size; i ++) {
            key_list.push_back(i);
        }
        shuffle(begin(key_list), end(key_list), rng);

        vector<int> key_accessed;
        GenZipf genzipf = GenZipf(alpha, key_list.size()); // zipf from 1 to size

        for (int i = 0; i < instance_size_max; i ++) {
            key_accessed.push_back(key_list[genzipf.get() - 1]);
        }

        for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
            string ds_name = dict->second;
            D* s = dict->first;

            timer.start();
            timer.pause();

            int counter = 0;
            int prev_instance_size = 0;
            // Set up
            for (auto it = key_list.begin(); it!=key_list.end(); it++) {
                s->emplace(*it, 0);
            }

            for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
                //cout << "\t" << instance_size << "\n";
                // Log
                out << ds_name << ",zipfAccessFixedInitialSize,"  << instance_size <<  "," << initial_size << "," << alpha << "," ;

                timer.resume();
                // One lap of the test
                for (int i = prev_instance_size; i < instance_size; i++) {
                    assert(s->contains(key_accessed[counter]));
                    counter++;
                }
                timer.pause(); out << timer.get_runtime() << "\n";
                prev_instance_size = instance_size;
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



void test_insert_from_fixed_initial_size(vector<pair<D*, string>>* dicts, int type) {
    //Insert from scratch but only time starting midway

    int instance_size_min = 16;
    int instance_size_max = 1<<17;
    int initial_size = 0;
    int min_iters = 100;
    int max_iters = 1000;
    int max_micro_sec = 1000 * 1000 * 60 * 5;

    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());

    string type_name;
    if (type == SORTED) {
        type_name = "Sorted";
    } else if (type == SHUFFLED) {
        type_name = "Shuffled";
    } else if (type == REVERSED) {
        type_name = "Reversed";
    } else {
        assert(false);
    }
    cout << type_name<< endl;

    ofstream out;
    out.open("insertFromFixedInitialSize" + type_name  +  ".csv");
    out << "data_structure,test_name,instance_size,initial_size,time_micro_seconds\n";

    Timer timer;

    start = GetTimeMicroS64();
    for (int iter = 0; iter < max_iters; iter++) {
        cout << iter << "\n";
        // Prepare key_list and access_list for all data structures
        vector<int> key_list;
        for (int i = 0; i < instance_size_max; i ++) {
            key_list.push_back(i);
        }
        if (type == SHUFFLED) {
            shuffle(begin(key_list), end(key_list), rng);
        } else if (type == REVERSED) {
            reverse(key_list.begin(), key_list.end());
        }

        for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
            string ds_name = dict->second;
            D* s = dict->first;

            timer.start();
            timer.pause();

            // Set up
            int counter;
            for (counter = 0; counter < initial_size; counter++) {
                cout << counter << "\t";
                cout << key_list[counter] << "\n";
                s->emplace(key_list[counter], 0);
            }
            int prev_instance_size = initial_size;

            for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
                //cout << "\t" << instance_size << "\n";
                // Log
                out << ds_name << ",insertFromFixedInitialSize,"  << instance_size <<  "," << initial_size << "," ;

                timer.resume();
                // One lap of the test
                for (; counter < instance_size; counter++) {
                    //cout << counter << "\t";
                    s->emplace(key_list[counter], 0);
                }
                timer.pause(); out << timer.get_runtime() << "\n";
                prev_instance_size = instance_size;
            }
            // Tear Down
            timer.reset(); s->clear();
        }
        if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
            break;
        }
    }
    out.close();
}

void test_inserts_varying_initial_size(vector<pair<D*, string>>* dicts) {
    //int instance_size_min = 16;
    //int num_accesses = 1<<14;
    //int instance_size_max = 1<<18;
    //int instance_size_min = 1<<18;
    //int num_inserts = 1<<14;
    //int min_iters = 1000;
    //int max_iters = 1000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;

    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());

    uniform_int_distribution<int> distribution;

    ofstream out;
    out.open("insertsVaryingInitialSize.csv");
    out << "data_structure,test_name,instance_size,num_inserts,time_micro_seconds\n";

    Timer timer;

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            cout << iter << "\n";
            // Prepare key_list and access_list for all data structures
            vector<int> key_list;
            for (int i = 0; i < instance_size + num_inserts; i++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);

            // For each iteration, for each key list, perform the same test
            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                // Log
                string ds_name = dict->second;
                D* s = dict->first;
                out << ds_name << ",insertsVaryingInitialSize,"  << instance_size <<  "," << num_inserts << ",";

                // Set Up
                int i;
                for (i = 0; i < instance_size; i++) {
                    s->emplace(key_list[i], 0);
                }
                timer.start();

                // Actual test
                for (; i < instance_size + num_inserts; i++) {
                    s->emplace(key_list[i], 0);
                }
                timer.pause(); out << timer.get_runtime() << "\n";

                // Tear Down
                timer.reset(); s->clear();
            }

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                cout << "\t" << iter << "\n";
                break;
            }
        }
    }
    out.close();
}

void test_deletes_varying_initial_size(vector<pair<D*, string>>* dicts) {
    //int instance_size_min = 16;
    //int num_accesses = 1<<14;
    //int instance_size_max = 1<<18;
    //int instance_size_min = 1<<18;
    //int num_deletes = 1<<14;
    //int min_iters = 1000;
    //int max_iters = 1000;
    int max_micro_sec = 1000 * 1000 * 3 * 1;

    uint64 start;
    std::random_device rng;
    std::mt19937 urng(rng());

    uniform_int_distribution<int> distribution;

    ofstream out;
    out.open("deletesVaryingInitialSize.csv");
    out << "data_structure,test_name,instance_size,num_deletes,time_micro_seconds\n";

    Timer timer;

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        start = GetTimeMicroS64();
        int iter;
        cout << instance_size << "\n";
        for (iter = 0; iter < max_iters; iter++) {
            // Prepare key_list and access_list for all data structures
            cout << iter << "\n";
            vector<int> key_list;
            for (int i = 0; i < instance_size; i++) {
                key_list.push_back(i);
            }
            shuffle(begin(key_list), end(key_list), rng);

            vector<int> key_list_copy = key_list;
            shuffle(begin(key_list_copy), end(key_list_copy), rng);

            vector<int> key_deletes;
            for (int i = 0; i < num_deletes; i++) {
                key_deletes.push_back(key_list_copy[i]);
            }

            // For each iteration, for each key list, perform the same test
            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                // Log
                string ds_name = dict->second;
                D* s = dict->first;
                out << ds_name << ",deletesVaryingInitialSize,"  << instance_size <<  "," << num_deletes << ",";

                // Set Up
                for (auto it = key_list.begin(); it!=key_list.end(); it++) {
                    s->emplace(*it, 0);
                }
                timer.start();

                // Actual test
                for (auto it = key_deletes.begin(); it != key_deletes.end(); it++) {
                    s->remove(*it);
                }
                timer.pause(); out << timer.get_runtime() << "\n";

                // Tear Down
                timer.reset(); s->clear();
            }

            if ((iter + 1 >= min_iters) && (int(GetTimeMicroS64() - start) > max_micro_sec)) {
                cout << "\t" << iter << "\n";
                break;
            }
        }
    }
    out.close();
}

void test_real_sequence(vector<pair<D*, string>>* dicts, string dataset) {
    //int min_iters = 10;
    //int max_micro_sec = 1000 * 1000 * 3 * 1;
    //uint64 start;

    //int max_iters = 1000;
    int max_iters = 1000;
    ofstream out;

    Timer timer;

    vector<int> elements_seq;
    vector<int> seq;
    map<char,int> m;

    int nb_operations;

    FILE * pFile;
    string path = "../data/anon/" + dataset + ".txt";
    pFile = fopen(path.c_str(),"r");
    //pFile = fopen ("../data/anon/bll.txt","r");
    fscanf (pFile, "%d", &nb_operations);

    for (int i = 0; i < nb_operations; i++) {
        int op, key;
        fscanf(pFile, "%d %d", &op, &key);
        seq.push_back(op);
        elements_seq.push_back(key);
    }
    fclose (pFile);
    out.open("testRealSequencelog" + dataset + ".csv");

      int iter;

      for (iter = 0; iter < max_iters; iter++) {
            cout << iter << "\n";

            for (auto dict = dicts->begin(); dict != dicts->end(); dict++) {
                // Log
                string ds_name = dict->second;
                D* s = dict->first;
                out << ds_name << ",RandomSequence_" + dataset + ","  << iter <<  ",";

                // Set Up
                timer.start();

                // Actual test
                for (int i = 0; i < nb_operations; i ++) {
                    if (seq[i] == 0){
                        timer.pause();
                        if (s->contains(elements_seq[i]) == 1){
                           timer.resume();
                            s->erase(elements_seq[i]);}
                        else{
                        timer.resume();}
                        }

                    if (seq[i] == 1){
                        timer.pause();

                       if (s -> contains(elements_seq[i])!=1){
                        timer.resume();
                        s->emplace(elements_seq[i],0);
                        }
                        else{
                        timer.resume();}
                        }

                    else if (seq[i] == 2){
                    s->contains(elements_seq[i]);
                    }
                            }
                timer.pause(); out << timer.get_runtime() << "\n";

                // Tear Down
                timer.reset(); s->clear();
            }
        }
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
    dicts.push_back(make_pair(new SplayTree, "SplayTree"));
    dicts.push_back(make_pair(new ZipTree(0.5, false), "ZipTree"));
    dicts.push_back(make_pair(new ZipTree(0.5, false, true), "ZipTreeFracRank"));
    dicts.push_back(make_pair(new ZipTree(0.5, false, false, true), "ZipTreeFindBeforeInsert"));
    dicts.push_back(make_pair(new ZipTree(0.5, true), "ZipTreeSelfAdjust"));
    dicts.push_back(make_pair(new SkipList(16, 0.5), "SkipList"));
    dicts.push_back(make_pair(new Treap, "Treap"));
    dicts.push_back(make_pair(new RedBlack, "RedBlack"));

    // Initial size = 1<<18
    // nb operations = 1<<14
    // nb iters = 1000
    //test_inserts_varying_initial_size(&dicts);
    //test_deletes_varying_initial_size(&dicts);
    //test_uniform_access_varying_initial_size(&dicts);
    //test_zipf_access_varying_initial_size(&dicts, 2);
    //test_zipf_access_varying_initial_size(&dicts, 1);
    //test_zipf_access_varying_initial_size(&dicts, 0.99);

    //test_zipf_varying_number_accesses_fixed_initial_size(&dicts);

    test_insert_from_fixed_initial_size(&dicts, SHUFFLED);
    test_insert_from_fixed_initial_size(&dicts, REVERSED);
    test_insert_from_fixed_initial_size(&dicts, SORTED);


    //vector<string> datasets;
    //datasets = {"bll", "br-actif", "br-support", "br", "faerix", "federez", "pasloin", "platal", "ragal", "root-br", "x", "x2013", "x2014"};
    //for (auto it = datasets.begin(); it != datasets.end(); it++) {
        //test_real_sequence(&dicts, *it);
    //}



    return 0;
}
