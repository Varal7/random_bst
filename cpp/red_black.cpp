#include "red_black.h"
#include <map>

using namespace std;

RedBlack::RedBlack() {
    m = new map<int, int>;
}


bool RedBlack::insert(int key, int value)  {
    m->emplace(key, value);
    // TODO: meaningful return values
    return true;
}

bool RedBlack::remove(int key) {
    m->erase(key);
    // TODO: meaningful return values
    return true;
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
