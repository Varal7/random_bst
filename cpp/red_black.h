#ifndef RED_BLACK_H
#define RED_BLACK_H

#include "dictionary.h"

class RedBlack : public Dictionary {
public:
    ZipTree();
    void insert(int key, int value);
    void remove(int key);
    ZipNode* search(int key);
    bool contains(int key);
    void display();
    void check();

private:
    ZipNode *root, *nullnode;
    float prob_;
    bool update_rank_, frac_rank_;
    int randomRank();
    ZipNode* search(ZipNode*& leaf, int key);
    void display(ZipNode*& leaf, int indent);
    void check(ZipNode*& leaf, int, int);
    void left_rot(ZipNode*& tree);
    void right_rot(ZipNode*& tree);
};

#endif
