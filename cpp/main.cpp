#include <iostream>
#include <cstdlib>
#include "zip_trees.h"
#include "treaps.h"

using namespace std;

int main() {
    srand(time(0));
    printf("Zip trees\n");
    ZipTree z;
    z.insert(1);
    z.insert(2);
    z.insert(3);
    z.insert(4);
    z.check();
    z.display();
    printf("\n");
    z.remove(2);
    z.display();
    z.check();

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
