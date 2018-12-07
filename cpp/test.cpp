#include "test.h"
#include "timer.h"
#include <stdio.h>

void Test::run() {
  instance_runtime_ = 0;
  tic = GetTimeMicroS64();
  running = true;
  execute_test();
  pause();
  status_code_ = TEST_PASS_;
}

void Test::pause() {
  assert(running == true);
  toc = GetTimeMicroS64();
  running = false;
  instance_runtime_ += int (toc-tic); // Runtime in micro seconds
}

void Test::resume() {
  assert(running == false);
  tic = GetTimeMicroS64();
  running = true;
}

int Test::get_runtime() {
  assert(status_code_ == TEST_PASS_);
  assert(running = false);
  return instance_runtime_;
}


int Test::get_status() {
  return status_code_;
}
