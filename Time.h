#ifndef INCLUDE_UTILITIES_TIME
#define INCLUDE_UTILITIES_TIME

#include "Common.h"

export uint64 Time_AddDays(uint64 time, int32 days);
export uint64 Time_AddHours(uint64 time, int32 hours);
export uint64 Time_AddMinutes(uint64 time, int32 minutes);
export uint64 Time_AddSeconds(uint64 time, int32 seconds);

#endif
