#include "dict_speed_test.h"
#include <random>

using namespace std;

// TestInsertFromRandList


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

// TestInsertFromList

TestInsertFromList::TestInsertFromList(vector<uint32>* key_list) {
  std::random_device rng;
  std::mt19937 urng(rng());
  key_list_ = key_list;
}


void TestInsertFromList::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
}

void TestInsertFromList::execute_test() {
  for (auto it = key_list_->begin(); it!=key_list_->end(); it++) {
      dict_->emplace(*it, 0);
  }
  status_code_ = TEST_PASS_;
}

// TestUniformAccessFixedStart

TestUniformAccessFixedStart::TestUniformAccessFixedStart(vector<int>* key_list, int num_accesses) {
  std::random_device rng;
  std::mt19937 urng(rng());
  key_list_ = key_list;
  num_accesses_ = num_accesses;
  distribution = uniform_int_distribution<int>(0, key_list_->size() -1); // unform distribution 0 <= x <= size -1
}


void TestUniformAccessFixedStart::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
  for (auto it = key_list_->begin(); it!=key_list_->end(); it++) {
      dict_->emplace(*it, 0);
  }
}

void TestUniformAccessFixedStart::execute_test() {
  for (int i = 0; i < num_accesses_; i++) {
      int off = distribution(urng);
      dict_->contains((*key_list_)[off]);
  }
  status_code_ = TEST_PASS_;
}

// TestZipfAccessFixedStart

TestZipfAccessFixedStart::TestZipfAccessFixedStart(vector<int>* key_list, int num_accesses, double alpha) {
  key_list_ = key_list;
  num_accesses_ = num_accesses;
  genzipf = new GenZipf(alpha, key_list_->size()); // zipf from 1 to size
}


void TestZipfAccessFixedStart::set_up(Dictionary* dict){
  status_code_ = TEST_INIT_;
  dict_ = dict;
  for (auto it = key_list_->begin(); it!=key_list_->end(); it++) {
      dict_->emplace(*it, 0);
  }
}

void TestZipfAccessFixedStart::execute_test() {
  for (int i = 0; i < num_accesses_; i++) {
      int off = genzipf->get() - 1;
      dict_->contains((*key_list_)[off]);
  }
  status_code_ = TEST_PASS_;
}
