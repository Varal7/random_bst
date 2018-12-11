#include <iostream>
#include <cstdlib>
#include "zip_trees.h"

using namespace std;

int main(int argc, char** argv) {
    int x;
    if (argc > 1) {
        x = atoi(argv[1]);
    } else {
        x = time(0);
    }
    cout << "seed: " << x << endl;
    srand(x);

    ZipTree z;
    cout << z.sum_depths() << endl;
    z.insert(0, 0);
    cout << z.sum_depths() << endl;
    for (int i = 1; i < 5; i ++) {
        z.insert(i, 0);
    }
    //z.insert(0, 0);
    //z.check();
    //z.insert(1, 0);
    z.display();
    z.check();
    cout << z.sum_depths() << endl;
    //z.insert(2, 0);
    //z.check();
    //z.insert(3, 0);
    //z.check();
    //z.remove(0);
    //z.check();
    //z.remove(1);
    //z.check();
    //z.remove(2);
    //z.check();
    //z.remove(3);
    //z.check();
}
