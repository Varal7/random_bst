#include <iostream>
#include <cstdlib>
#include <vector>
#include <assert.h>
#include "zip_trees.h"
#include "treaps.h"
#include "skip_list.h"

#ifndef TEST_INIT_
#define TEST_INIT_ 0
#endif

#ifndef TEST_PASS_
#define TEST_PASS_ 1
#endif

#ifndef TEST_FAIL_
#define TEST_FAIL_ -1
#endif

#ifndef TEST_H_
#define TEST_H_

typedef long int32; typedef unsigned long uint32;

// Generic test harness class
class Test
{
public:
  // Constructor and destructor
  virtual ~Test() {};
  // Member functions
  void run(); // Public fn that wraps execute_test & logs runtime, status
  //void set_up();
  int get_runtime(); // Get runtime in ms
  int get_status();
protected:
  virtual void execute_test() =0; // Private fn that executes test
  uint32 instance_size_;
  int instance_runtime_; // Runtime in ms
  int status_code_;
};

#endif
