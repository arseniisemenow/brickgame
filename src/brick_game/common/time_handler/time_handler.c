#include "time_handler.h"

#include <stddef.h>

long long GetTimeInMS() {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}