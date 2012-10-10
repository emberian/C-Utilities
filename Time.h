#ifndef INCLUDE_UTILITIES_TIME
#define INCLUDE_UTILITIES_TIME

#include "Common.h"

public uint64 Time_AddDays(uint64 time, int32 days);
public uint64 Time_AddHours(uint64 time, int32 hours);
public uint64 Time_AddMinutes(uint64 time, int32 minutes);
public uint64 Time_AddSeconds(uint64 time, int32 seconds);
public uint64 Time_NowPlusDays(int32 days);
public uint64 Time_NowPlusHours(int32 hours);
public uint64 Time_NowPlusMinutes(int32 minutes);
public uint64 Time_NowPlusSeconds(int32 seconds);

#endif
