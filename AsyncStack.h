#ifndef INCLUDE_UTILITIES_ASYNCSTACK
#define INCLUDE_UTILITIES_ASYNCSTACK

#include "Common.h"
#include "Stack.h"
#include <SAL/Thread.h>

typedef struct {
	SAL_Mutex Lock;
	Stack* BaseStack;
} AsyncStack;

export AsyncStack* AsyncStack_New(uint64 size);
export void AsyncStack_Initialize(AsyncStack* stack, uint64 size);
export void AsyncStack_Free(AsyncStack* self);
export void AsyncStack_Uninitialize(AsyncStack* self);
export void AsyncStack_PushUInt64(AsyncStack* self, uint64 value);
export void AsyncStack_PushUInt32(AsyncStack* self, uint32 value);
export void AsyncStack_PushUInt16(AsyncStack* self, uint16 value);
export void AsyncStack_PushUInt8(AsyncStack* self, uint8 value);
export void AsyncStack_PushInt64(AsyncStack* self, int64 value);
export void AsyncStack_PushInt32(AsyncStack* self, int32 value);
export void AsyncStack_PushInt16(AsyncStack* self, int16 value);
export void AsyncStack_PushInt8(AsyncStack* self, int8 value);
export uint64 AsyncStack_PopUInt64(AsyncStack* self);
export uint32 AsyncStack_PopUInt32(AsyncStack* self);
export uint16 AsyncStack_PopUInt16(AsyncStack* self);
export uint8 AsyncStack_PopUInt8(AsyncStack* self);
export int64 AsyncStack_PopInt64(AsyncStack* self);
export int32 AsyncStack_PopInt32(AsyncStack* self);
export int16 AsyncStack_PopInt16(AsyncStack* self);
export int8 AsyncStack_PopInt8(AsyncStack* self);

#endif
