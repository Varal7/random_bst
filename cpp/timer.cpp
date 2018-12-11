#include "timer.h"
#include <assert.h>

uint64 GetTimeMicroS64()
{
 struct timeval tv;

 gettimeofday(&tv, NULL);

 uint64 ret = tv.tv_usec;
 /* Uncomment following line to Convert from micro seconds (10^-6) to milliseconds (10^-3) */
 //ret /= 1000;

 /* Adds the seconds (10^0) after converting them to microsconds (10^-6) */
 ret += (tv.tv_sec * 1000 * 1000);

 return ret;
}


Timer::Timer() {
  status_code = STOPPED_;
  cur_time = 0;
}

void Timer::start() {
  assert(status_code == STOPPED_);
  assert(cur_time == 0);
  status_code = RUNNING_;
  tic = GetTimeMicroS64();
}

void Timer::pause() {
  toc = GetTimeMicroS64();
  assert(status_code == RUNNING_);
  status_code = PAUSED_;
  cur_time += int(toc - tic);
}

void Timer::resume() {
  assert(status_code == PAUSED_);
  status_code = RUNNING_;
  tic = GetTimeMicroS64();
}

void Timer::reset() {
  assert(status_code == PAUSED_);
  status_code = STOPPED_;
  cur_time = 0;
}

int Timer::get_runtime() {
  assert(status_code == PAUSED_);
  return cur_time;
}
