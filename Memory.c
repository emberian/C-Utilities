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
void* Memory_AllocateD(uint64 size, uint64 line, int8* file) {
	/*if (!allocationsInitialized) allocations = LinkedList_New( ( void(*)(void*) ) String_Free);*/

	return malloc(size);
}

void* Memory_ReallocateD(void* block, uint64 size, uint64 line, int8* file) {
	/*if (!allocationsInitialized) allocations = LinkedList_New( ( void(*)(void*) ) String_Free);*/

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

void Memory_BlockCopy(uint8* source, uint8* destination, uint64 amount) {
	uint8 i;

	if (amount > 0) {
		for (; amount >= 8; amount -= 8) 
			*(uint64*)(destination + amount - 8) = *(uint64*)(source + amount - 8);

		for (i = 0; i < amount; i++)
			*(uint8*)(destination + i) = *(source + i);
	}
}

boolean Memory_Compare(uint8* blockA, uint8* blockB, uint64 lengthA, uint64 lengthB) {
	if (lengthA != lengthB)
		return false;

	for (; lengthA > 0; lengthA--)
		if (blockA[lengthA - 1] != blockB[lengthA - 1])
			return false;

	return true;
}