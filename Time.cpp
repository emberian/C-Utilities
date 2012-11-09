#include "Time.h"

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
