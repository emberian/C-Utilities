#ifndef CUTILITIES_INCLUDE_COMMON
#define CUTILITIES_INCLUDE_COMMON

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <Software-Abstraction-Layer/Common.h>

#define Allocate(type) ((type*)malloc(sizeof(type)))
#define AllocateArray(type, count) ((type*)malloc(sizeof(type) * count))
#define true 1
#define false 0
#define null NULL

#ifdef WINDOWS
	#define export __declspec(dllexport)
#elif defined POSIX
	#define export ;
#endif

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef double float64;
typedef float float32;
typedef int8 boolean;

#endif