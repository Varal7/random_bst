/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c

WITH MEMORY USAGE LOG
*/

#include "dictionary.h"
#include "splay_tree.h"
#include "mem_log.h"

#ifndef SPLAY_TREE_LOG_H_
#define SPLAY_TREE_LOG_H_

class SplayTreeLogged : public SplayTree
{
public:
  SplayTreeLogged();
  // Member functions for dictionary ADT
  void insert(int search_key, int new_value);
  void remove(int search_key);
  SplayNode* search(int search_key);
  bool contains(int search_key);
  void check();
  // The memory log
  static MemLog *log_;
private:
  SplayNode *root_;
  void splay(int search_key);
};

#endif  // SPLAY_TREE_PC_H_
