#include "Time.h"

#include <SAL/Time.h>

uint64 Time_AddDays(uint64 time, int32 days) {
	return time + (days * 24 * 60 * 60 * 1000);
}

uint64 Time_AddHours(uint64 time, int32 hours) {
	return time + (hours * 60 * 60 * 1000);
}

uint64 Time_AddMinutes(uint64 time, int32 minutes) {
	return time + (minutes * 60 * 1000);
}

uint64 Time_AddSeconds(uint64 time, int32 seconds) {
	return time + (seconds * 1000);
}

uint64 Time_NowPlusDays(int32 days) {
	return SAL_Time_Now() + (days * 24 * 60 * 60 * 1000);
}

uint64 Time_NowPlusHours(int32 hours) {
	return SAL_Time_Now() + (hours * 60 * 60 * 1000);

}

uint64 Time_NowPlusMinutes(int32 minutes) {
	return SAL_Time_Now() + (minutes * 60 * 1000);

}

uint64 Time_NowPlusSeconds(int32 seconds) {
	return SAL_Time_Now() + (seconds * 1000);

}