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

void Stack_PushUInt64(Stack* self, uint64 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushUInt32(Stack* self, uint32 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushUInt16(Stack* self, uint16 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushUInt8(Stack* self, uint8 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushInt64(Stack* self, int64 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushInt32(Stack* self, int32 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushInt16(Stack* self, int16 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

void Stack_PushInt8(Stack* self, int8 value) {
	Array_Write(&self->Data, (uint8*)&value, self->Pointer, sizeof(value));
	self->Pointer += sizeof(value);
}

uint64 Stack_PopUInt64(Stack* self) {
	assert(self->Pointer >= sizeof(uint64));
	self->Pointer -= sizeof(uint64);
	return *(uint64*)Array_Read(&self->Data, self->Pointer, sizeof(uint64));
}

uint32 Stack_PopUInt32(Stack* self) {
	assert(self->Pointer >= sizeof(uint32));
	self->Pointer -= sizeof(uint32);
	return *(uint32*)Array_Read(&self->Data, self->Pointer, sizeof(uint32));
}

uint16 Stack_PopUInt16(Stack* self) {
	assert(self->Pointer >= sizeof(uint16));
	self->Pointer -= sizeof(uint16);
	return *(uint16*)Array_Read(&self->Data, self->Pointer, sizeof(uint16));
}

uint8 Stack_PopUInt8(Stack* self) {
	assert(self->Pointer >= sizeof(uint8));
	self->Pointer -= sizeof(uint8);
	return *(uint8*)Array_Read(&self->Data, self->Pointer, sizeof(uint8));
}

int64 Stack_PopInt64(Stack* self) {
	assert(self->Pointer >= sizeof(int64));
	self->Pointer -= sizeof(int64);
	return *(int64*)Array_Read(&self->Data, self->Pointer, sizeof(int64));
}

int32 Stack_PopInt32(Stack* self) {
	assert(self->Pointer >= sizeof(int32));
	self->Pointer -= sizeof(int32);
	return *(int32*)Array_Read(&self->Data, self->Pointer, sizeof(int32));
}

int16 Stack_PopInt16(Stack* self) {
	assert(self->Pointer >= sizeof(int16));
	self->Pointer -= sizeof(int16);
	return *(int16*)Array_Read(&self->Data, self->Pointer, sizeof(int16));
}

int8 Stack_PopInt8(Stack* self) {
	assert(self->Pointer >= sizeof(int8));
	self->Pointer -= sizeof(int8);
	return *(int8*)Array_Read(&self->Data, self->Pointer, sizeof(int8));
}
