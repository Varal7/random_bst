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

/*
// Splay node copy constructor
SplayNode::SplayNode(const SplayNode &obj) {
  left = obj.left;
  right = obj.right;
}
*/

/*
SplayNode::~SplayNode() {
  delete left;
  delete right;
}
*/

uint32_t SplayNode::height() {
  if (left != nullptr && right != nullptr) {
  return (left->height() > right->height()) ?
    left->height() + 1 : right->height() + 1;
  } else if (left != nullptr) {
  return left->height() + 1;
  } else if (right != nullptr) {
  return right->height() + 1;
  } else return 0;
}

// Splay tree constructors
SplayTree::SplayTree() {
  root_ = nullptr;
}

/*
SplayTree::SplayTree(const SplayTree &obj) {
  root_ = obj.root_;
}
*/

SplayTree::SplayTree(SplayNode *root) {
  root_ = root;
}

/*
SplayTree::~SplayTree() {
  delete root_;
  return;
}
*/

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
  t->left = n.right;
  t->right = n.left;
  root_ = t;
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

// Insert a new key into a tree and return true, unless it is already there.
// In that case, overwrite and return false.
bool SplayTree::insert(int search_key, int new_value) {

  splay(search_key);
  SplayNode* new_node = new SplayNode(search_key, new_value, nullptr, nullptr);

  // If tree is empty, simply insert the new node as root.
  if (root_ == nullptr) {
    root_ = new_node;
    return true;
  }

  if (root_->key == search_key) {
    root_->value = new_value;
    delete new_node;
    return false;
  }
  // The possibilities are now: search_key < t.key and search_key > root_.key
  else if (search_key < root_->key) {
	  new_node->left = root_->left;
	  new_node->right = root_;
	  root_->left = nullptr;
    root_ = new_node;
  }
  else { // i.e. search_key > root_.key
	  new_node->right = root_->right;
	  new_node->left = root_;
	  root_->right = nullptr;
    root_ = new_node;
    }
  return true;
}

// Try to remove a node and return true if it is found in the tree. Return false
// otherwise.
bool SplayTree::remove(int search_key) {

  if (root_ == nullptr) {
    return false;
  }

  SplayNode* t;
  splay(search_key);
    if (root_->key == search_key) {
	    if (root_->left == nullptr) {
        t = root_;
	      root_ = t->right;
        delete t;
        return true;
	    } else {
        t = root_;
        SplayTree left_subtree = SplayTree(t->left);
	      left_subtree.splay(search_key);
	      left_subtree.root_->right = t->right;
        root_ = left_subtree.root_;
        t->left = t->right = nullptr;
        delete t;
        return true;
	    }
    }
    return false;
}


void SplayTree::check()
{
  //TOOD
  return;
}
