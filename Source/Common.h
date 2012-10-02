#ifndef INCLUDE_COMMON
#define INCLUDE_COMMON

#include <assert.h>
#include <stdlib.h>

#define Allocate(type) ((type*)malloc(sizeof(type)))
#define AllocateArray(type, count) ((type*)malloc(sizeof(type) * count))
#define true 1
#define false 0
#define null 0

#ifdef _WIN64
	#define export __declspec(dllexport)
#elif __unix__
	#define export ;
#endif


typedef long long int64;
typedef int int32;
typedef short int16;
typedef char int8;
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef double float64;
typedef float float32;
typedef char boolean;

export uint8 FooFunc(void);

#endif
