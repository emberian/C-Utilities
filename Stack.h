#ifndef INCLUDE_UTILITIES_STACK
#define INCLUDE_UTILITIES_STACK

#include "Common.h"
#include "Array.h"

typedef struct {
	Array Data;
	uint64 Pointer;
} Stack;

public Stack* Stack_New(uint64 size);
public void Stack_Initialize(Stack* stack, uint64 size);
public void Stack_Free(Stack* self);
public void Stack_Uninitialize(Stack* self);
public void Stack_Push(Stack* self, void* value);
public void* Stack_Pop(Stack* self);

#endif
