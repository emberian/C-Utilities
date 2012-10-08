#ifndef CUTILITIES_INCLUDE_COMMON
#define CUTILITIES_INCLUDE_COMMON

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <Software-Abstraction-Layer/Common.h>

/**
 * @returns a pointer to a block of memory at least the sizeof @a type.
 */
#define Allocate(type) ((type*)malloc(sizeof(type)))

/**
 * @returns a pointer to a block of memory large enough to contain @a count
 * objects of size @a type.
 */
#define AllocateArray(type, count) ((type*)malloc(sizeof(type) * count))

/**
 * Frees a block of memory allocated by Allocate or AllocateArray
 * @param pointer The block of memory to free
 */
#define Free(pointer) free(pointer)

#define true 1
#define false 0
#define null NULL

#ifdef WINDOWS
	#define public  __declspec(dllexport)
#elif defined __clang__ || defined __GNUC__
	#define public __attribute__((visibility ("default")))
#endif

#ifdef WINDOWS
// Windows is private by default
  #define private ;
#elif defined __clang__ || defined __GNUC__
  #define private __attribute__((visibility ("hidden")))
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
