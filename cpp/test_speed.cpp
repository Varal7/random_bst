#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"
#include "splay_tree.h"
#include "splay_tree_logged.h"
#include "dict_speed_test.h"
#include <map>

using namespace std;


typedef Dictionary D;

void test_speed() {
    Dictionary *s;
    int instance_size_min = 16;
    int instance_size_max = 1<<20;
    int max_iters = 1;

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        for (int iter = 0; iter < max_iters; iter++) {
            TestInsertFromRandList *dst = new TestInsertFromRandList(instance_size);
            printf("SkipList insertFromRand %d ", instance_size);
            s = new SkipList(16, 0.5);
            dst->set_up(s); dst->run();
            cout << dst->get_runtime() << "\n";
            delete s;
        }
    }

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        for (int iter = 0; iter < max_iters; iter++) {
            TestInsertFromRandList *dst = new TestInsertFromRandList(instance_size);
            printf("ZipTree insertFromRand %d ", instance_size);
            s = new ZipTree();
            dst->set_up(s); dst->run();
            cout << dst->get_runtime() << "\n";
            delete s;
        }
    }

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        for (int iter = 0; iter < max_iters; iter++) {
            TestInsertFromRandList *dst = new TestInsertFromRandList(instance_size);
            printf("SplayTree insertFromRand %d ", instance_size);
            s = new SplayTree();
            dst->set_up(s); dst->run();
            cout << dst->get_runtime() << "\n";
            delete s;
        }
    }

    for (int instance_size = instance_size_min; instance_size <= instance_size_max; instance_size *= 2) {
        for (int iter = 0; iter < max_iters; iter++) {
            TestInsertFromRandList *dst = new TestInsertFromRandList(instance_size);
            printf("Treap insertFromRand %d ", instance_size);
            s = new Treap();
            dst->set_up(s); dst->run();
            cout << dst->get_runtime() << "\n";
            delete s;
        }
    }


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

    test_speed();
    return 0;
}
