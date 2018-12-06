#include <iostream>
#include <map>
#include "genzipf.h"

using namespace std;

void test_genzipf() {
    cout << "Zip'f distribution" << endl;
    GenZipf* g = new GenZipf(0.5, 20);
    map<int, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[g->get()];
    }
    for(auto p : hist) {
        cout << p.first <<
                ' ' << string(p.second/100, '*') << '\n';
    }
}

int main() {
    test_genzipf();
}
