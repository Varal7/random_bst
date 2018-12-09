#ifndef TREAPS_H_
#define TREAPS_H_

#include "dictionary.h"

struct TreapNode : Item
{
    int priority;
    TreapNode *left, *right;
};


class Treap : public Dictionary {
public:
    Treap();
    bool insert(int key, int value);
    bool remove(int key);
    TreapNode* search(int key);
    bool contains(int key);
    void display();
    void check();

protected:
    TreapNode *root, *nullnode;
    bool insert(TreapNode*& leaf, int key, int value);
    bool remove(TreapNode*& leaf, int key);
    bool remove(TreapNode*& leaf);
    void left_rot(TreapNode*& leaf);
    void right_rot(TreapNode*& leaf);
    TreapNode* search(TreapNode*& leaf, int key);
    void display(TreapNode*& leaf, int indent);
    void check(TreapNode*& leaf, int, int);
    int height();
    int height(TreapNode*& leaf);
};

#endif
