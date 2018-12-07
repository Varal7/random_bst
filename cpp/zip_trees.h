#ifndef ZIP_TREES_H
#define ZIP_TREES_H

#include "dictionary.h"

// TODO: add value

struct ZipNode : Item
{
    int rank;
    ZipNode *left, *right;
};

class ZipTree : public Dictionary {
public:
    ZipTree(float prob=0.5, bool update_rank_on_access=false, bool use_frac_rank=false);
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
