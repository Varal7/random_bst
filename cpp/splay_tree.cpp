/*
Top-down splay tree heavily modeled on C implementation of D. Sleator, from
https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c
*/

#include "splay_tree.h"


// Splay node constructor
SplayNode::SplayNode(int k, int v, SplayNode *l, SplayNode *r)
  : left(l), right(r) {
    key = k;
    value = v;
}

// Splay tree constructor
SplayTree::SplayTree() {
  root_ = nullptr;
}

SplayTree::~SplayTree() {
  // TODO
  return;
}


 void SplayTree::splay(int search_key) {
/* Simple top down splay, not requiring search_key to be in the tree.  */
  SplayNode n(0,0,nullptr,nullptr), *r, *l, *y;
  r = l = &n;
  SplayNode *t = root_;

  if (t == nullptr) {
    return;
  }

  for (;;) {
	  if (search_key < t->key) {
	  if (t->left == nullptr) break;
      if (search_key < t->left->key) {
		    y = t->left;                           /* rotate right */
		    t->left = y->right;
        y->right = t;
	      t = y;
		    if (t->left == nullptr) break;
	    }
    r->left = t;                               /* link right */
	  r = t;
	  t = t->left;
  } else if (search_key > t->key) {
	    if (t->right == nullptr) break;
	    if (search_key > t->right->key) {
		    y = t->right;                          /* rotate left */
		    t->right = y->left;
		    y->left = t;
		    t = y;
		    if (t->right == nullptr) break;
	    }
	    l->right = t;                              /* link left */
	    l = t;
	    t = t->right;
	  } else {
	  break;
	  }
  }
  l->right = t->left;                                /* assemble */
  r->left = t->right;
  t->left = nullptr;
  t->right = nullptr;
}

SplayNode* SplayTree::search(int search_key) {
  splay(search_key);

  if (root_ == nullptr) {
    return nullptr;
  }

  if (root_->key == search_key) {
    return root_;
  } else {
    return nullptr;
  }
}

void SplayTree::insert(int search_key, int new_value) {
/* Insert new key into tree, unless it's already there.    */
  splay(search_key);
  SplayNode* t = root_;

  // If tree is empty, simply insert the new node as root.
  if (t == nullptr) {
    SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr);
    root_ = new_node;
    return;
  }

  if (root_->key == search_key) {
    root_->value = new_value;
    return;
  }
  // The possibilities are now: search_key < t.key and search_key > root_.key
  else if (search_key < root_->key) {
    SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr);
	  new_node->left = root_->left;
	  new_node->right = root_;
	  root_->left = nullptr;
    root_ = new_node;
  }
  else { // i.e. search_key > root_.key
    SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr);
	  new_node->right = root_->right;
	  new_node->left = root_;
	  root_->right = nullptr;
    root_ = new_node;
    }
}

void SplayTree::remove(int search_key) {

  if (root_ == nullptr) {
    return;
  }

  SplayNode* t;
  splay(search_key);
    if (root_->key == search_key) {
	    if (root_->left == nullptr) {
        t = root_;
	      root_ = t->right;
        delete t;
	    } else {
        t = root_;
        SplayTree left_subtree = SplayTree();
	      left_subtree.splay(search_key);
	      left_subtree.root_->right = t->right;
        root_ = left_subtree.root_;
        delete t;
	    }
    }
}

void SplayTree::check()
{
  //TOOD
  return;
}
