#ifndef INCLUDE_UTILITIES_MEMORY
#define INCLUDE_UTILITIES_MEMORY

#include "Common.h"

public void Memory_Free(void* block);
public void Memory_BlockCopy(const uint8* source, uint8* destination, uint64 amount);

/**
 * Frees a block of memory allocated by Allocate or AllocateArray
 * @param pointer The block of memory to free
 */
#define Free(pointer) Memory_Free(pointer)

#ifdef NDEBUG

    public void* Memory_Allocate(uint64 size);
    public void* Memory_Reallocate(void* block, uint64 size);

    /**
     * @returns a pointer to a block of memory at least the sizeof @a type.
     */
    #define Allocate(type) ((type*)Memory_Allocate(sizeof(type)))

    /**
     * @returns a pointer to a block of memory large enough to contain @a count
     * objects of size @a type.
     */
    #define AllocateArray(type, count) ((type*)Memory_Allocate(sizeof(type) * count))

    /**
     * @returns a pointer to a block of memory large enough to contain @a count
     * objects of size @a type.
     */
    #define ReallocateArray(type, count, array) ((type*)Memory_Reallocate((void*)array, sizeof(type) * count))

#else

    public void* Memory_AllocateD(uint64 size, uint64 line, const int8* file);
    public void* Memory_ReallocateD(void* block, uint64 size, uint64 line, const int8* file);

    #define Allocate(type) ((type*)Memory_AllocateD(sizeof(type), __LINE__, __FILE__))
    #define AllocateArray(type, count) ((type*)Memory_AllocateD(sizeof(type) * count, __LINE__, __FILE__))
    #define ReallocateArray(type, count, array) ((type*)Memory_ReallocateD((void*)array, sizeof(type) * count, __LINE__, __FILE__))

#endif


#endif
