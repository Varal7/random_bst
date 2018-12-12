#ifndef SKIP_LIST_LOGGED_H_
#define SKIP_LIST_LOGGED_H_

#include <vector>
#include "dictionary.h"
#include "skip_list.h"
#include "mem_log.h"


class SkipListLogged : public SkipList
{
public:
  SkipListLogged(int max_level, float prob);//(int max_level=32, float prob=0.5);
  //  : SkipList(max_level, prob) { log_->incr_size(sizeof(SkipList)); };
  //~SkipListLogged();
  // methods of the data structure
  bool insert(int search_key, int new_value);
  bool remove(int search_key);
  SkipNode* search(int search_key);
  bool contains(int search_key);
  void check();
  float potential();
  static MemLog *log_;
};

#endif  // SkipList_H_
