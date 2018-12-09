/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c

WITH MEMORY USAGE LOG
*/

#ifndef SPLAY_TREE_LOG_H_
#define SPLAY_TREE_LOG_H_

#include "dictionary.h"
#include "splay_tree.h"
#include "mem_log.h"


class SplayTreeLogged : public SplayTree
{
public:
  SplayTreeLogged();
  SplayTreeLogged(SplayNode *root);
  // Member functions for dictionary ADT
  bool insert(int search_key, int new_value);
  bool remove(int search_key);
  SplayNode* search(int search_key);
  bool contains(int search_key);
  void check();
  // Bookkeeping functions
  uint32_t depth();
  // The memory log
  static MemLog *log_;
protected:
  void splay(int search_key);
};

#endif  // SPLAY_TREE_PC_H_
