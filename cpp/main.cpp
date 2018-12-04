#include <iostream>
#include <cstdlib>
#include <vector>
#include <assert.h>
#include "zip_trees.h"
#include "treaps.h"

using namespace std;

int main() {
    srand(time(0));

    vector<int> list;

    for (int i = 0; i < 1000; i ++) {
        list.push_back(i);
    }


    printf("Zip trees\n");
    ZipTree z;

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        z.insert(*it);
        z.check();
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        assert(z.contains(*it));
    }

    random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        z.remove(*it);
        z.check();
        assert(!(z.contains(*it)));
    }
    printf("Test passed\n");

    printf("\nTreaps\n");
    Treap t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.check();
    t.display();
    printf("\n");
    t.remove(2);
    t.display();
    t.check();
}
