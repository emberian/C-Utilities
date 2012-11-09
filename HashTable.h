#ifndef INCLUDE_UTILITIES_HASHTABLE
#define INCLUDE_UTILITIES_HASHTABLE

#include "Common.h"

typedef struct HashTable HashTable;

HashTable* HashTable_New();
void HashTable_Initialize(HashTable* table);
void HashTable_Free(HashTable* self);
void HashTable_Uninitialize(HashTable* self);

uint8* HashTable_Get(HashTable* self, uint8* key, uint32 keyLength, uint8** value, uint32* valueLength); //returns the value as well in case the length is already known.
void HashTable_Add(HashTable* self, uint8* key, uint32 keyLength, uint8* value, uint32 valueLength);
void HashTable_Remove(HashTable* self, uint8* key, uint32 keyLength);
uint8* HashTable_GetInt(HashTable* self, uint64 key, uint8** value, uint32* valueLength);
void HashTable_AddInt(HashTable* self, uint64 key, uint8* value, uint32 valueLength);
void HashTable_RemoveInt(HashTable* self, uint64 key);

#endif
