#include "dict_correctness_test.h"

DictCorrectnessTest::DictCorrectnessTest(uint32 instance_size) {
  instance_size_ = instance_size;
}


void DictCorrectnessTest::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
  std::vector<uint32> key_list_;
  for (uint32 i = 0; i < instance_size_; i ++) {
      key_list_.push_back(i);
  }
}

void DictCorrectnessTest::execute_test() {
  std::random_shuffle(key_list_.begin(), key_list_.end());
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->insert(*it, 0);
      dict_->check();
  }

  std::random_shuffle(key_list_.begin(), key_list_.end());
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      assert(dict_->contains(*it));
  }

  std::random_shuffle(key_list_.begin(), key_list_.end());
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->remove(*it);
      dict_->check();
      assert(!(dict_->contains(*it)));
  }
}


int DictCorrectnessTest::get_runtime() {
  assert(status_code_ != 0);
  return instance_runtime_;
}


int DictCorrectnessTest::get_status() {
  return status_code_;
}
