#include "dict_log_test.h"
#include <random>

auto lt_rng = std::default_random_engine {};

DictLogTest::DictLogTest(uint32 instance_size) {
  instance_size_ = instance_size;
}


void DictLogTest::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
  key_list_.clear();
  for (uint32 i = 0; i < instance_size_; i ++) {
      key_list_.push_back(i);
  }
}

void DictLogTest::execute_test() {
  shuffle(begin(key_list_), end(key_list_), lt_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->insert(*it, 0);
  }

  shuffle(begin(key_list_), end(key_list_), lt_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
  }

  shuffle(begin(key_list_), end(key_list_), lt_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->remove(*it);
  }
  status_code_ = TEST_PASS_;
}
