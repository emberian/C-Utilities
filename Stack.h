#ifndef INCLUDE_UTILITIES_STACK
#define INCLUDE_UTILITIES_STACK

#include "Common.h"
#include "Array.h"

typedef struct {
	Array Data;
	uint64 Pointer;
} Stack;

export Stack* Stack_New(uint64 size);
export void Stack_Initialize(Stack* stack, uint64 size);
export void Stack_Free(Stack* self);
export void Stack_Uninitialize(Stack* self);
export void Stack_Push(Stack* self, void* value);
export void* Stack_Pop(Stack* self);

#endif
