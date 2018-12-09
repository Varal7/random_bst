/*
A log-keeping version of the skip-list class. Note that none of the methods
defined herein are optimized for performance. Some are quite slow.
*/


#include "skip_list.h"
#include "skip_list_logged.h"

#if __APPLE__
#elif __linux__
    #include <bits/stdc++.h>
#elif __unix__ // all unices not caught above
#else
#endif

// Define the log object
MemLog *SkipListLogged::log_ = new MemLog();


// Skip list constructor
SkipListLogged::SkipListLogged(int max_level, float prob)
: SkipList(max_level, prob) {
  log_->incr_size(sizeof(SkipList));
}

/*
// Skip list destructor
SkipListLogged::~SkipListLogged()
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
*/


// Add a new key-value pair.
bool SkipListLogged::insert(int search_key, int new_value)
{
  bool node_inserted = SkipList::insert(search_key, new_value);
  if (node_inserted) {
    // Not all skip list nodes are the same size, so we need to find the node
    // that we just inserted and find out how big it was. This looks pretty
    // braindead, but these methods are not striving for performance.

    // TODO: this also might be _wrong_...
    log_->incr_size(sizeof(search(search_key)));
  }
  return node_inserted;
}


bool SkipListLogged::remove(int search_key)
{
  bool node_removed = SkipList::remove(search_key);
  if (node_removed) {
    log_->incr_size(-int(sizeof(search(search_key))));
  }
  return node_removed;
}


// Seek an existing SkipNode by key.
SkipNode* SkipListLogged::search(int search_key)
{
  SkipNode* node =SkipList::search(search_key);
  return node;
}

void SkipListLogged::check()
{
  // TODO
  return;
}
