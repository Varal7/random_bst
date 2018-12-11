#ifndef ZIP_TREES_H_
#define ZIP_TREES_H_

#include "dictionary.h"


using namespace std;

struct ZipNode : Item
{
    int rank;
    ZipNode *left, *right;
    uint32_t height();
};

class ZipTree : public Dictionary {
public:
    ZipTree(
            float prob=0.5,
            bool update_rank_on_access=false,
            bool use_frac_rank=false,
            bool find_before_insert=false);
    bool insert(int key, int value);
    bool remove(int key);
    ZipNode* search(int key);
    bool contains(int key);
    void display();
    void check();
    int height();
    int count_nodes();
    int sum_depths();
    void clear();
    double potential();
protected:
    ZipNode *root;
    float prob_;
    bool update_rank_, frac_rank_;
    bool find_before_insert_;
    int randomRank();
    ZipNode* search(ZipNode*& leaf, int key);
    int height(ZipNode*& leaf);
    int count_nodes(ZipNode*& leaf);
    void display(ZipNode*& leaf, int indent);
    void check(ZipNode*& leaf, int, int);
    void left_rot(ZipNode*& tree);
    void right_rot(ZipNode*& tree);
    void clear(ZipNode*& leaf);
    bool insert_(int key, int value);
    int sum_depths(ZipNode*& leaf, int depth);
    pair<int, double> potential(ZipNode*& leaf);
};

#endif
