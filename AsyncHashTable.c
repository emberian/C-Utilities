#include "AsyncHashTable.h"
#include "HashTable.h"
#include <SAL/Thread.h>

struct AsyncHashTable {
	HashTable* BaseTable;
	SAL_Mutex Lock;
};

AsyncHashTable* AsyncHashTable_New() {
	AsyncHashTable* table;
	
	table = Allocate(AsyncHashTable);
	AsyncHashTable_Initialize(table);

	return table;
}

void AsyncHashTable_Initialize(AsyncHashTable* table) {
	uint16 i;

	assert(table != NULL);

	table->BaseTable = HashTable_New();
	table->Lock = SAL_Mutex_Create();
}

void AsyncHashTable_Free(AsyncHashTable* self) {
	AsyncHashTable_Uninitialize(self);

	Free(self);
}

void AsyncHashTable_Uninitialize(AsyncHashTable* self) {
	assert(self != NULL);

	HashTable_Free(self->BaseTable);
	SAL_Mutex_Free(self->Lock);
}

uint8* AsyncHashTable_Get(AsyncHashTable* self, uint8* key, uint32 keyLength, uint8** value, uint32* valueLength) {
	uint8* result;

	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	result = HashTable_Get(self->BaseTable, key, keyLength, value, valueLength);
	SAL_Mutex_Release(self->Lock);

	return result;
}

void AsyncHashTable_Add(AsyncHashTable* self, uint8* key, uint32 keyLength, uint8* value, uint32 valueLength) {
	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	HashTable_Add(self->BaseTable, key, keyLength, value, valueLength);
	SAL_Mutex_Release(self->Lock);
}

void AsyncHashTable_Remove(AsyncHashTable* self, uint8* key, uint32 keyLength) {
	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	HashTable_Remove(self->BaseTable, key, keyLength);
	SAL_Mutex_Release(self->Lock);
}

uint8* AsyncHashTable_GetInt(AsyncHashTable* self, uint64 key, uint8** value, uint32* valueLength) {
	uint8* result;

	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	result = HashTable_GetInt(self->BaseTable, key, value, valueLength);
	SAL_Mutex_Release(self->Lock);

	return result;
}

void AsyncHashTable_AddInt(AsyncHashTable* self, uint64 key, uint8* value, uint32 valueLength) {
	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	HashTable_AddInt(self->BaseTable, key, value, valueLength);
	SAL_Mutex_Release(self->Lock);
}

void AsyncHashTable_RemoveInt(AsyncHashTable* self, uint64 key) {
	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	HashTable_RemoveInt(self->BaseTable, key);
	SAL_Mutex_Release(self->Lock);
}
