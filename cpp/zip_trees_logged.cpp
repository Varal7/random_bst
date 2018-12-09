#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "zip_trees.h"
#include "zip_trees_logged.h"

using namespace std;

// Define the log object
MemLog *ZipTreeLogged::log_ = new MemLog();

// Constructor for a logged zip tree
ZipTreeLogged::ZipTreeLogged(float prob, bool update_rank, bool frac_rank)
: ZipTree(prob, update_rank, frac_rank) {
    log_->incr_size(sizeof(ZipTree));
}

// Compute the depth of the tree as the height of its root
uint32_t ZipTreeLogged::depth() {
  if (root == nullptr) {
    return 0;
  }
  return ZipTree::height();
}


bool ZipTreeLogged::insert(int key, int value) {
  bool node_inserted = ZipTree::insert(key, value);
  if (node_inserted) {
    log_->incr_size(sizeof(ZipNode));
  }
  log_->update_greatest_depth(this->depth());
  return node_inserted;
}


bool ZipTreeLogged::remove(int key) {
  bool node_removed = ZipTree::remove(key);
  if (node_removed) {
    log_->incr_size(-int(sizeof(ZipNode)));
  }
  log_->update_greatest_depth(this->depth());
  return node_removed;
}


ZipNode* ZipTreeLogged::search(int key) {
    return ZipTree::search(key);
}
