#include "Memory.h"
#include "LinkedList.h"
#include "Strings.h"

#include <stdlib.h>


#ifdef NDEBUG

    void* Memory_Allocate(uint64 size) {
        return malloc(size);
    }

    void* Memory_Reallocate(void* block, uint64 size) {
        return realloc(block, size);
    }

#else

    LinkedList* allocations;
    static boolean allocationsInitialized = false;

    //add a record of the allocation to allocations and remove it on FreeD()
    void* Memory_AllocateD(uint64 size, uint64 line, const int8* file) {
        if (!allocationsInitialized) allocations = LinkedList_New( ( void(*)(void*) ) String_Dispose);

        return malloc(size);
    }

    void* Memory_ReallocateD(void* block, uint64 size, uint64 line, const int8* file) {
        if (!allocationsInitialized) allocations = LinkedList_New( ( void(*)(void*) ) String_Dispose);

        return realloc(block, size);
    }

#endif


void Memory_Free(void* block) {
    #ifdef NDEBUG
        free(block);
    #else
        free(block);
    #endif
}
