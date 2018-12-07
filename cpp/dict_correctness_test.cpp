#include "dict_correctness_test.h"
#include <random>

auto ct_rng = std::default_random_engine {};

DictCorrectnessTest::DictCorrectnessTest(uint32 instance_size) {
  instance_size_ = instance_size;
}


void DictCorrectnessTest::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
  key_list_.clear();
  for (uint32 i = 0; i < instance_size_; i ++) {
      key_list_.push_back(i);
  }
}

void DictCorrectnessTest::execute_test() {
  shuffle(begin(key_list_), end(key_list_), ct_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->insert(*it, 0);
      dict_->check();
  }

  shuffle(begin(key_list_), end(key_list_), ct_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      assert(dict_->contains(*it));
  }

  shuffle(begin(key_list_), end(key_list_), ct_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->remove(*it);
      dict_->check();
      assert(!(dict_->contains(*it)));
  }
  status_code_ = TEST_PASS_;
}


int DictCorrectnessTest::get_runtime() {
  assert(status_code_ != 0);
  return instance_runtime_;
}


int DictCorrectnessTest::get_status() {
  return status_code_;
}
