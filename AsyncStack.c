#include "AsyncStack.h"

AsyncStack* AsyncStack_New(uint64 size) {
	AsyncStack* stack;

	stack = Allocate(AsyncStack);

	AsyncStack_Initialize(stack, size);

	return stack;
}

void AsyncStack_Initialize(AsyncStack* stack, uint64 size) {
	assert(stack != NULL);
	stack->BaseStack = Stack_New(size);
	stack->Lock = SAL_Mutex_Create();
}

void AsyncStack_Free(AsyncStack* self) {
	assert(self != NULL);
	AsyncStack_Uninitialize(self);
	Free(self);
}

void AsyncStack_Uninitialize(AsyncStack* self) {
	assert(self != NULL);
	Stack_Free(self->BaseStack);
	SAL_Mutex_Free(&self->Lock);
}

void AsyncStack_Push(AsyncStack* self, void* value) {
	assert(self != NULL);
	SAL_Mutex_Acquire(self->Lock);
	Stack_Push(self->BaseStack, value);
	SAL_Mutex_Release(self->Lock);
}

void* AsyncStack_Pop(AsyncStack* self) {
	void* result;
	
	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	result = Stack_Pop(self->BaseStack);
	SAL_Mutex_Release(self->Lock);

	return result;
}