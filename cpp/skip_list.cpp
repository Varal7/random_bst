#include "skip_list.h"


// SkipNode constructor
SkipNode::SkipNode(int k, int v, int l) : key(k), value(v), level(l)
// Allocate space for forward vector.
{
  forward.reserve(level);
}


// Skip list constructor
SkipList::SkipList(int max_level, float prob)
  : max_level_(max_level), prob_(prob)
{
  level_ = 0;           // No real SkipNodes yet
  header_ = new SkipNode(INT_MIN, 0, max_level_);
  nil_ = new SkipNode(INT_MAX, 0, max_level_);
  for( int i = 0; i < max_level_; i++) {
    header_->forward[i] = nil_;
    nil_->forward[i] = nullptr;
  }
}


// Skip list destructor
SkipList::~SkipList()
{
  // Delete all non-nil SkipNodes
  SkipNode* x = header_;
  SkipNode* y;
  while (x->forward[0] != nil_) {
    y = x;
    x = x->forward[0];
    delete y;
  }
  // And then the nil SkipNode.
  delete nil_;
}

// Calculate a random level to be assigned to a SkipNode.
inline int SkipList::random_level()
{
  int lvl = 1;
  while ((float) rand()/(float) RAND_MAX < prob_)
    lvl++;
  return lvl;
}


// Add a new key-value pair.
void SkipList::insert(int search_key, int new_value)
{
  // Vector of rightmost SkipNodes at each level to left of inserted SkipNode
  std::vector<SkipNode*> update(max_level_);
  // Maintain the current SkipNode
  SkipNode* x = header_;
  for(int i = level_ - 1; i >= 0; i--) {
      while (x->forward[i] != nil_ && x->forward[i]->key < search_key) {
        x = x->forward[i];
      }
      // Set the search path values
      update[i] = x;
  }
  x = x->forward[0];

  // Update value if key is already in the skip list.
  if (x->key == search_key) {
    x->value = new_value;
  }

  //Otherwise, insert the new key-value pair.
  else {
    int new_level = random_level();
    // Update the list's level if the new new SkipNode is higher-level
    if (new_level > level_) {
      for (int i = level_; i < new_level; i++) {
        update[i] = header_;
      }
      level_ = new_level;
    }
    // Allocate a new SkipNode for the inserted key-value pair and set key, value.
    SkipNode* x = new SkipNode(search_key, new_value, new_level);
    // Stitch the new SkipNode into the list by moving local pointers.
    for (int i = 0; i < new_level; i++) {
      x->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = x;
    }
  }
}

void SkipList::remove(int search_key)
{
  // Vector of rightmost SkipNodes at each level to left of inserted SkipNode
  std::vector<SkipNode*> update(max_level_);
  // Maintain the current SkipNode
  SkipNode* x = header_;
  for(int i = level_ - 1; i >= 0; i--) {
      while (x->forward[i] != nil_ && x->forward[i]->key < search_key) {
        x = x->forward[i];
      }
      // Set the search path values
      update[i] = x;
  }
  x = x->forward[0];
  // Now remove the key-value pair
  if (x->key == search_key) {
    for (int i = 0; i < level_; i++) {
      if (update[i]->forward[i] != x) break;
      update[i]->forward[i] = x->forward[i];
    }
    delete x;
  }
  while (level_ > 1 && header_->forward[level_] == nil_) {
    level_ = level_-1;
  }
}


// Seek an existing SkipNode by key.
SkipNode* SkipList::search(int search_key)
{
  // Start looking at the data structure's entry point
  SkipNode* x = header_;
  // Loop invariant: x-> < search_key
  for (int i = level_ - 1; i >= 0; i--) {
    while ((x->forward[i] != nil_) && (x->forward[i]->key < search_key)) {
      x = x->forward[i];
    }
  }
  // x->key < search_key <= x->forward[0]->key
  x = x->forward[0];
  if (x->key == search_key) {
    return x;
  } else {
    return nullptr;
  }
}
