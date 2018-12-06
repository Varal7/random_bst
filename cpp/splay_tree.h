/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c
*/

#include "dictionary.h"

#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

struct SplayNode : public Item
{
    int key, value;
    SplayNode *left, *right;
    SplayNode(int k, int v, SplayNode *l, SplayNode *r);
};

class SplayTree : public Dictionary
{
public:
  SplayTree();
  ~SplayTree();
  // Member functions for dictionary ADT
  void insert(int search_key, int new_value);
  void remove(int search_key);
  SplayNode* search(int search_key);
  bool contains(int search_key);
  void check();

private:
    SplayNode *root_;
    void splay(int search_key);
};

#endif  // SPLAY_TREE_H_
