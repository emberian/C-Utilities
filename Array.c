#include "Array.h"

Array* Array_New(uint64 size) {
    Array* array;
    
    array = Allocate(Array);
    Array_Initialize(array, size);

    return array;
}

Array* Array_NewFromExisting(uint8* data, uint64 size) {
    Array* array;
    uint64 actualSize;
    
    assert(size > 0);
    assert(data != NULL);
    
    actualSize = 32;
    while (actualSize < size)
        actualSize *= 2;

    array = Allocate(Array);
    array->Size = size;
    array->Allocation = actualSize;
    array->Data = ReallocateArray(uint8, actualSize, data);

    return array;
}

void Array_Initialize(Array* array, uint64 size) {
    uint64 actualSize;

    assert(array != NULL);

    actualSize = 32;
    while (actualSize < size)
        actualSize *= 2;
        
    array->Size = size;
    array->Allocation = actualSize;
    array->Data = AllocateArray(uint8, actualSize);
}

void Array_Dispose(Array* self) {
    assert(self != NULL);

    Free(self->Data);
    self->Size = 0;
    self->Allocation = 0;
}

void Array_Resize(Array* self, uint64 newSize) {
    uint64 actualSize;

    assert(newSize > 0);
    assert(self != NULL);

    actualSize = self->Allocation;
    while (actualSize < newSize)
        actualSize *= 2;

    if (actualSize != self->Allocation) self->Data = ReallocateArray(uint8, actualSize, self->Data);
    self->Allocation = actualSize;
    self->Size = newSize;
}

uint8* Array_Read(Array* self, uint64 position, uint64 amount) {
    assert(self != NULL);
    assert(position + amount <= self->Size);

    return self->Data + position;
}

void Array_Write(Array* self, const uint8* data, uint64 position, uint64 amount) {
    uint8 i;

    assert(self != NULL);
    
    if (position + amount > self->Size) Array_Resize(self, position + amount);

    for (i = 0; i < amount; i++)
        *(self->Data + position + i) = *(data + i);
}

void Array_Append(Array* self, Array* source) {
    assert(self != NULL && source != NULL);

    Array_Resize(self, self->Size + source->Size);
    Array_Write(self, source->Data, self->Size, source->Size);
}