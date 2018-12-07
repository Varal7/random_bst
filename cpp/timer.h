#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <ctime>

typedef long long int64; typedef unsigned long long uint64;

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

#endif
