#ifndef INCLUDE_UTILITIES_HASHTABLE
#define INCLUDE_UTILITIES_HASHTABLE

#include "Common.h"

typedef struct HashTable HashTable;

export HashTable* HashTable_New();
export void HashTable_Initialize(HashTable* table);
export void HashTable_Free(HashTable* self);
export void HashTable_Uninitialize(HashTable* self);

export void* HashTable_Get(HashTable* self, uint8* key, uint32 keyLength, void** value, uint32* valueLength); //returns the value as well in case the length is already known.
export void HashTable_Add(HashTable* self, uint8* key, uint32 keyLength, void* value, uint32 valueLength);
export void HashTable_Remove(HashTable* self, uint8* key, uint32 keyLength);
export void* HashTable_GetInt(HashTable* self, uint64 key, void** value, uint32* valueLength);
export void HashTable_AddInt(HashTable* self, uint64 key, void* value, uint32 valueLength);
export void HashTable_RemoveInt(HashTable* self, uint64 key);

#define HashTable_GetIntType(table, key, type) (type)HashTable_GetInt((table), (key), NULL, NULL)
#define HashTable_AddIntType(table, key, value) HashTable_AddInt((table), (key), (void*)(value), sizeof(value))
#define HashTable_GetType(table, key, type) (type)HashTable_Get((table), (uint8*)(key), sizeof(key), NULL, NULL)
#define HashTable_AddType(table, key, value) HashTable_Add((table), (uint8*)(key), sizeof(key), (void*)(value), sizeof(value))

#endif
