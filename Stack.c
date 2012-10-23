#include "Stack.h"

Stack* Stack_New(uint64 size) {
	Stack* stack;

	stack = Allocate(Stack);

	Stack_Initialize(stack, size);

	return stack;
}

void Stack_Initialize(Stack* stack, uint64 size) {
	stack->Pointer = 0;
	Array_Initialize(&stack->Data, size);
}

void Stack_Free(Stack* self) {
	Stack_Uninitialize(self);
	Free(self);
}

void Stack_Uninitialize(Stack* self) {
	Array_Free(&self->Data);
	self->Pointer = 0;
}

void Stack_Push(Stack* self, void* value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(void*));
	self->Pointer += sizeof(void*);
}

void* Stack_Pop(Stack* self) {
	assert(self->Pointer >= sizeof(void*));
	self->Pointer -= sizeof(void*);
	return (void*)Array_Read(&self->Data, self->Pointer, sizeof(void*));
}
