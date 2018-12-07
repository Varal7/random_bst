#ifndef TREAPS_H
#define TREAPS_H

#include "dictionary.h"

struct TreapNode : Item
{
    int priority;
    TreapNode *left, *right;
};


class Treap : public Dictionary {
public:
    Treap();
    void insert(int key, int value);
    void remove(int key);
    TreapNode* search(int key);
    bool contains(int key);
    void display();
    void check();

private:
    TreapNode *root, *nullnode;
    void insert(TreapNode*& leaf, int key, int value);
    void remove(TreapNode*& leaf, int key);
    void remove(TreapNode*& leaf);
    void left_rot(TreapNode*& leaf);
    void right_rot(TreapNode*& leaf);
    TreapNode* search(TreapNode*& leaf, int key);
    void display(TreapNode*& leaf, int indent);
    void check(TreapNode*& leaf, int, int);
};

#endif
