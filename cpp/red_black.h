#ifndef RED_BLACK_H
#define RED_BLACK_H

#include "dictionary.h"
#include <map>

using namespace std;

class RedBlack : public Dictionary {
public:
    RedBlack();
    bool insert(int key, int value);
    bool remove(int key);
    Item* search(int key);
    bool contains(int key);
    void check();
    void clear();
    int height();
private:
    map<int, int> *m;
};

#endif
