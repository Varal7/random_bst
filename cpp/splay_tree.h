/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c
*/

#include "dictionary.h"
#include <stdint.h>
#include <algorithm>

#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

struct SplayNode : public Item
{
    SplayNode *left, *right;
    SplayNode(int k, int v, SplayNode *l, SplayNode *r);
    //SplayNode(const SplayNode &obj);
    //~SplayNode();
    uint32_t height();
};

class SplayTree : public Dictionary
{
public:
  SplayTree();
  SplayTree(SplayNode *root);
  //SplayTree(const SplayTree &obj);
  //~SplayTree();
  // Member functions for dictionary ADT
  bool insert(int search_key, int new_value);
  bool remove(int search_key);
  SplayNode* search(int search_key);
  bool contains(int search_key);
  void check();
protected:
  void splay(int search_key);
  SplayNode *root_;
  int height();
  int height(SplayNode*& leaf);
};

#endif  // SPLAY_TREE_H_
