#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "treaps.h"
#include "treaps_logged.h"

using namespace std;

// Define the log object
MemLog *TreapLogged::log_ = new MemLog();

// Constructor for a logged treap
TreapLogged::TreapLogged() {
    log_->incr_size(sizeof(Treap));
}


uint32_t TreapLogged::depth() {
  if (root == nullptr) {
    return 0;
  }
  return Treap::height();
}


bool TreapLogged::insert(int key, int value) {
  bool node_inserted = Treap::insert(key, value);
  if (node_inserted) {
    log_->incr_size(sizeof(TreapNode));
  }
  log_->update_greatest_depth(this->depth());
  return node_inserted;
}


bool TreapLogged::remove(int key) {
  bool node_removed = Treap::remove(key);
  if (node_removed) {
    log_->incr_size(-int(sizeof(TreapNode)));
  }
  log_->update_greatest_depth(this->depth());
  return node_removed;
}


TreapNode* TreapLogged::search(int key) {
  return Treap::search(key);
}
