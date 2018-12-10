/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c
*/

#include "splay_tree.h"
#include "splay_tree_logged.h"

// Define the log object
MemLog *SplayTreeLogged::log_ = new MemLog();

/*
SplayTree::SplayTree(const SplayTree &obj) {
  root_ = obj.root_;
}
*/

// Logged splay tree constructors
SplayTreeLogged::SplayTreeLogged() {
  root_ = nullptr;
  log_->incr_size(sizeof(SplayTree)); // Set initial size to BARE splay tree.
}


SplayTreeLogged::SplayTreeLogged(SplayNode *root) {
  root_ = root;
  log_->incr_size(sizeof(SplayTree)); // Set initial size to BARE splay tree.
}


void SplayTreeLogged::splay(int search_key) {
  SplayTree::splay(search_key);
  log_->update_greatest_depth(this->height());
}


uint32_t SplayTreeLogged::height() {
  if (root_ == nullptr) {
    return 0;
  }
  return SplayTree::height();
}

SplayNode* SplayTreeLogged::search(int search_key) {
  SplayNode *node = SplayTree::search(search_key);
  log_->update_greatest_depth(this->height());
  return node;
}


bool SplayTreeLogged::insert(int search_key, int new_value) {
  bool node_inserted = SplayTree::insert(search_key, new_value);
  if (node_inserted) {
    log_->incr_size(sizeof(SplayNode));
  }
  log_->update_greatest_depth(this->height());
  return node_inserted;
}


bool SplayTreeLogged::remove(int search_key) {
  bool node_removed = SplayTree::remove(search_key);
  if (node_removed) {
    log_->incr_size(-int(sizeof(SplayNode)));
  }
  log_->update_greatest_depth(this->height());
  return node_removed;
}


void SplayTreeLogged::check()
{
  //TOOD
  return;
}
