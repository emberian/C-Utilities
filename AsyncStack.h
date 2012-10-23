#ifndef INCLUDE_UTILITIES_ASYNCSTACK
#define INCLUDE_UTILITIES_ASYNCSTACK

#include "Common.h"
#include "Stack.h"
#include <SAL/Thread.h>

typedef struct {
	SAL_Mutex Lock;
	Stack* BaseStack;
} AsyncStack;

public AsyncStack* AsyncStack_New(uint64 size);
public void AsyncStack_Initialize(AsyncStack* stack, uint64 size);
public void AsyncStack_Free(AsyncStack* self);
public void AsyncStack_Uninitialize(AsyncStack* self);
public void AsyncStack_PushUInt64(AsyncStack* self, uint64 value);
public void AsyncStack_PushUInt32(AsyncStack* self, uint32 value);
public void AsyncStack_PushUInt16(AsyncStack* self, uint16 value);
public void AsyncStack_PushUInt8(AsyncStack* self, uint8 value);
public void AsyncStack_PushInt64(AsyncStack* self, int64 value);
public void AsyncStack_PushInt32(AsyncStack* self, int32 value);
public void AsyncStack_PushInt16(AsyncStack* self, int16 value);
public void AsyncStack_PushInt8(AsyncStack* self, int8 value);
public uint64 AsyncStack_PopUInt64(AsyncStack* self);
public uint32 AsyncStack_PopUInt32(AsyncStack* self);
public uint16 AsyncStack_PopUInt16(AsyncStack* self);
public uint8 AsyncStack_PopUInt8(AsyncStack* self);
public int64 AsyncStack_PopInt64(AsyncStack* self);
public int32 AsyncStack_PopInt32(AsyncStack* self);
public int16 AsyncStack_PopInt16(AsyncStack* self);
public int8 AsyncStack_PopInt8(AsyncStack* self);

#endif
