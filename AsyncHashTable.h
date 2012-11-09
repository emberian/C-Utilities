#ifndef INCLUDE_UTILITIES_ASYNCHASHTABLE
#define INCLUDE_UTILITIES_ASYNCHASHTABLE

#include "Common.h"

typedef struct AsyncHashTable AsyncHashTable;

public AsyncHashTable* AsyncHashTable_New();
public void AsyncHashTable_Initialize(AsyncHashTable* table);
public void AsyncHashTable_Free(AsyncHashTable* self);
public void AsyncHashTable_Uninitialize(AsyncHashTable* self);

public uint8* AsyncHashTable_Get(AsyncHashTable* self, uint8* key, uint32 keyLength, uint8** value, uint32* valueLength); //returns the value as well in case the length is already known.
public void AsyncHashTable_Add(AsyncHashTable* self, uint8* key, uint32 keyLength, uint8* value, uint32 valueLength);
public void AsyncHashTable_Remove(AsyncHashTable* self, uint8* key, uint32 keyLength);
public uint8* AsyncHashTable_GetInt(AsyncHashTable* self, uint64 key, uint8** value, uint32* valueLength);
public void AsyncHashTable_AddInt(AsyncHashTable* self, uint64 key, uint8* value, uint32 valueLength);
public void AsyncHashTable_RemoveInt(AsyncHashTable* self, uint64 key);

#endif
