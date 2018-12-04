#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

struct SplayNode
{
    int key, value;
    SplayNode *left, *right;
    SplayNode(int k, int v);
};

class SplayTree : public Dictionary
{
public:
  SkipList(int max_level, float prob);
  ~SkipList();
  // Member functions for dictionary ADT
  void insert(int search_key, int new_value);
  void remove(int search_key);
  SplayNode* search(int search_key);

private:
    SplayNode *root, *nullnode;
    void rot_l(SplayNode* root);
    void rot_r(SplayNode* root);
    void rot_ll(SplayNode* topn);
    void rot_lr(SplayNode* parent);
    void rot_rl(SplayNode* parent);
    void rot_rr(SplayNode* parent);
    void splay(SplayNode* root, int key);
};

#endif  // SPLAY_TREE_H_
