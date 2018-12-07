#include "test.h"
#include <random>
#include <vector>

#ifndef DICT_SPEED_TEST_H_
#define DICT_SPEED_TEST_H_

using namespace std;

class TestInsertFromRandList : public Test
{
public:
  TestInsertFromRandList(uint32 instance_size);
  void set_up(Dictionary* dict); // Stage an empty dictionary for the test
private:
  void execute_test();
  Dictionary* dict_;
  std::vector<uint32> key_list_;
  uint32 instance_size_;
  std::mt19937 urng;
};

class TestInsertFromList : public Test
{
public:
  TestInsertFromList(vector<uint32>*);
  void set_up(Dictionary* dict); // Stage an empty dictionary for the test
private:
  void execute_test();
  Dictionary* dict_;
  std::vector<uint32> *key_list_;
  std::mt19937 urng;
};

class TestUniformAccessFixedStart : public Test
{
public:
  TestUniformAccessFixedStart(vector<int>*, int);
  void set_up(Dictionary* dict); // Stage an empty dictionary for the test
private:
  void execute_test();
  Dictionary* dict_;
  std::vector<int> *key_list_;
  std::mt19937 urng;
  int num_accesses_;
  uniform_int_distribution<int> distribution;
};


#endif
