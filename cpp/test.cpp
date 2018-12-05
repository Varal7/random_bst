#include "test.h"
#include "timer.h"
#include <stdio.h>

void Test::run() {
  uint64 tic, toc;
  //assert(get_status() == 32767);
  tic = GetTimeMs64();
  execute_test();
  toc = GetTimeMs64();
  instance_runtime_ = int (toc-tic); // Runtime in ms
  status_code_ = TEST_PASS_;
}

int Test::get_runtime() {
  assert(status_code_ == TEST_PASS_);
  return instance_runtime_;
}


int Test::get_status() {
  return status_code_;
}
