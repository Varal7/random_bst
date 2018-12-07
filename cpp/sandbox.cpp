#include <iostream>
#include <cstdlib>
#include "zip_trees.h"

using namespace std;

int main() {
    ZipTree z;
    z.insert(0, 0);
    z.check();
    z.insert(1, 0);
    z.check();
    z.insert(2, 0);
    z.check();
    z.insert(3, 0);
    z.check();
    z.remove(0);
    z.check();
    z.remove(1);
    z.check();
    z.remove(2);
    z.check();
    z.remove(3);
    z.check();
}
