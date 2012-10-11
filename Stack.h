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
public void Stack_PushUInt64(Stack* self, uint64 value);
public void Stack_PushUInt32(Stack* self, uint32 value);
public void Stack_PushUInt16(Stack* self, uint16 value);
public void Stack_PushUInt8(Stack* self, uint8 value);
public void Stack_PushInt64(Stack* self, int64 value);
public void Stack_PushInt32(Stack* self, int32 value);
public void Stack_PushInt16(Stack* self, int16 value);
public void Stack_PushInt8(Stack* self, int8 value);
public uint64 Stack_PopUInt64(Stack* self);
public uint32 Stack_PopUInt32(Stack* self);
public uint16 Stack_PopUInt16(Stack* self);
public uint8 Stack_PopUInt8(Stack* self);
public int64 Stack_PopInt64(Stack* self);
public int32 Stack_PopInt32(Stack* self);
public int16 Stack_PopInt16(Stack* self);
public int8 Stack_PopInt8(Stack* self);

#endif
