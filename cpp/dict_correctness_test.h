#include "test.h"

#ifndef DICT_CORRECTNESS_TEST_H_
#define DICT_CORRECTNESS_TEST_H_

class DictCorrectnessTest : public Test
{
public:
  DictCorrectnessTest(uint32 instance_size);
  void set_up(Dictionary* dict); // Stage an empty dictionary for the test
protected:
  void execute_test();
  uint32 instance_size_;
  int instance_runtime_;
  int status_code_;
private:
  Dictionary* dict_;
  // The data of the test
  std::vector<uint32> key_list_;
};

#endif
