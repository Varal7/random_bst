#include "test.h"
#include <random>

#ifndef DICT_SPEED_TEST_H_
#define DICT_SPEED_TEST_H_

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

#endif
