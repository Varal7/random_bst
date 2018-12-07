#include "red_black.h"
#include <map>

using namespace std;

RedBlack::RedBlack() {
    m = new map<int, int>;
}


void RedBlack::insert(int key, int value)  {
    m->emplace(key, value);
}

void RedBlack::remove(int key) {
    m->erase(key);
}

Item* RedBlack::search(int key) {
    auto it = m->find(key);
    if (it == m->end()) {
        return nullptr;
    }
    Item* el = new Item;
    el->key = it->first;
    el->value = it->second;
    return el;
}

void RedBlack::check() {
}
