/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c

WITH MEMORY USAGE LOG
*/

#include "splay_tree.h"
#include "splay_tree_logged.h"

// Define the log object
MemLog *SplayTreeLogged::log_ = new MemLog();

// Splay tree constructor
SplayTreeLogged::SplayTreeLogged() {
  root_ = nullptr;
  log_->incr_size(sizeof(SplayTree)); // Set initial size to BARE splay tree.
}

void SplayTreeLogged::splay(int search_key) {
/* Simple top down splay, not requiring search_key to be in the tree.  */
  SplayNode n(0,0,nullptr,nullptr), *r, *l, *y;
  r = l = &n; log_->incr_ptr_ops_asn(2);
  SplayNode *t = root_; log_->incr_ptr_ops_asn(1);

  if (t == nullptr) {
    return;
  }

  for (;;) {
	  if (search_key < t->key) {
      log_->incr_ptr_ops_ref(1);
	  if (t->left == nullptr) {log_->incr_ptr_ops_ref(1); break;}
      if (search_key < t->left->key) {
        log_->incr_ptr_ops_ref(2);
		    y = t->left; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);              /* rotate right */
		    t->left = y->right; log_->incr_ptr_ops_ref(2); log_->incr_ptr_ops_asn(1);
        y->right = t; log_->incr_ptr_ops_asn(1); log_->incr_ptr_ops_ref(1);
	      t = y; log_->incr_ptr_ops_asn(1);
		    if (t->left == nullptr) { log_->incr_ptr_ops_ref(1); break;}
	    }
    r->left = t; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);               /* link right */
	  r = t; log_->incr_ptr_ops_asn(1);
	  t = t->left; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
  } else if (search_key > t->key) {
      log_->incr_ptr_ops_ref(1);
	    if (t->right == nullptr) {log_->incr_ptr_ops_ref(1); break;}
	    if (search_key > t->right->key) {
        log_->incr_ptr_ops_ref(2);
		    y = t->right; log_->incr_ptr_ops_asn(1); log_->incr_ptr_ops_ref(1);  /* rotate left */
		    t->right = y->left; log_->incr_ptr_ops_asn(1); log_->incr_ptr_ops_ref(2);
		    y->left = t; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
		    t = y; log_->incr_ptr_ops_asn(1);
		    if (t->right == nullptr) {log_->incr_ptr_ops_ref(1); break;}
	    }
	    l->right = t; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);                   /* link left */
	    l = t; log_->incr_ptr_ops_asn(1);
	    t = t->right; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
	  } else {
	  break;
	  }
  }
  l->right = t->left; log_->incr_ptr_ops_ref(2); log_->incr_ptr_ops_asn(1);                              /* assemble */
  r->left = t->right; log_->incr_ptr_ops_ref(2); log_->incr_ptr_ops_asn(1);
  t->left = nullptr; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
  t->right = nullptr; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
}

SplayNode* SplayTreeLogged::search(int search_key) {
  splay(search_key);

  if (root_ == nullptr) {
    return nullptr;
  }

  if (root_->key == search_key) {
    log_->incr_ptr_ops_ref(1);
    return root_;
  } else {
    return nullptr;
  }
}

void SplayTreeLogged::insert(int search_key, int new_value) {
/* Insert new key into tree, unless it's already there.    */
  splay(search_key);
  SplayNode* t = root_; log_->incr_ptr_ops_asn(1);

  // If tree is empty, simply insert the new node as root.
  if (t == nullptr) {
    SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr); log_->incr_ptr_ops_asn(1);
    root_ = new_node; log_->incr_size(sizeof(SplayNode));
    return;
  }

  if (root_->key == search_key) {
    log_->incr_ptr_ops_ref(1);
    root_->value = new_value; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
    return;
  }
  // The possibilities are now: search_key < t.key and search_key > root_.key
  else if (search_key < root_->key) {
    log_->incr_ptr_ops_ref(1);
    SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr); log_->incr_ptr_ops_asn(1);
	  new_node->left = root_->left; log_->incr_ptr_ops_ref(2); log_->incr_ptr_ops_asn(1);
	  new_node->right = root_; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
	  root_->left = nullptr; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
    root_ = new_node; log_->incr_ptr_ops_asn(1); log_->incr_size(sizeof(SplayNode));
  }
  else { // i.e. search_key > root_.key
    SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr); log_->incr_ptr_ops_asn(1);
	  new_node->right = root_->right; log_->incr_ptr_ops_ref(2); log_->incr_ptr_ops_asn(1);
	  new_node->left = root_; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
	  root_->right = nullptr; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
    root_ = new_node; log_->incr_ptr_ops_asn(1); log_->incr_size(sizeof(SplayNode));
    }
}

void SplayTreeLogged::remove(int search_key) {

  if (root_ == nullptr) {
    return;
  }

  SplayNode* t;
  splay(search_key);
    if (root_->key == search_key) {
      log_->incr_ptr_ops_ref(1);
	    if (root_->left == nullptr) {
        log_->incr_ptr_ops_ref(1);
        t = root_; log_->incr_ptr_ops_asn(1);
	      root_ = t->right; log_->incr_ptr_ops_ref(1); log_->incr_ptr_ops_asn(1);
        delete t; log_->incr_size(-int(sizeof(SplayNode)));
	    } else {
        t = root_; log_->incr_ptr_ops_asn(1);
        SplayTreeLogged left_subtree = SplayTreeLogged();
	      left_subtree.splay(search_key);
	      left_subtree.root_->right = t->right; left_subtree.log_->incr_ptr_ops_ref(2); left_subtree.log_->incr_ptr_ops_asn(1);
        root_ = left_subtree.root_; log_->incr_ptr_ops_asn(1);
        delete t; log_->incr_size(-int(sizeof(SplayNode)));
	    }
    }
}

void SplayTreeLogged::check()
{
  //TOOD
  return;
}
