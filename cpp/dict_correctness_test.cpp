#include "dict_correctness_test.h"
#include <random>
#include <iostream>

using namespace std;

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
  //cout << "\tInserting\n";
  shuffle(begin(key_list_), end(key_list_), ct_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->insert(*it, 0);
      dict_->check();
  }

  //cout << "\tAccessing\n";
  shuffle(begin(key_list_), end(key_list_), ct_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      assert(dict_->contains(*it));
  }

  //cout << "\tRemoving\n";
  shuffle(begin(key_list_), end(key_list_), ct_rng);
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->remove(*it);
      dict_->check();
      assert(!(dict_->contains(*it)));
  }

  //cout << "\tInserting again\n";
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      dict_->insert(*it, 0);
  }
  //cout << "\tClear\n";
  dict_->clear();
  for (auto it = key_list_.begin(); it!=key_list_.end(); it++) {
      assert(!(dict_->contains(*it)));
  }
  status_code_ = TEST_PASS_;
}


