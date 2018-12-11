#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <ctime>

#ifndef STOPPED_
#define STOPPED_ 0
#endif

#ifndef RUNNING_
#define RUNNING_ 1

#ifndef PAUSED_
#define PAUSED_ 2
#endif

typedef long int32; typedef unsigned long uint32;
typedef long long int64; typedef unsigned long long uint64;
uint64 GetTimeMicroS64();


class Timer
{
public:
  Timer();
  void start();
  void pause();
  void resume();
  void reset();
  int get_runtime();
private:
  int cur_time; // Runtime in micro seconds
  int status_code;
  uint64 tic, toc;
};

#endif
#endif
