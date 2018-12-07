#include "dict_speed_test.h"
#include <random>


TestInsertFromRandList::TestInsertFromRandList(uint32 instance_size) {
  std::random_device rng;
  std::mt19937 urng(rng());
  instance_size_ = instance_size;
}


void TestInsertFromRandList::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
  key_list_.clear();
  for (uint32 i = 0; i < instance_size_; i ++) {
      key_list_.push_back(i);
  }
}

void TestInsertFromRandList::execute_test() {
  pause();
  shuffle(begin(key_list_), end(key_list_), urng);
  resume();
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->emplace(*it, 0);
  }
  status_code_ = TEST_PASS_;
}
