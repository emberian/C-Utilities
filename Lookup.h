#ifndef INCLUDE_UTILITIES_LOOKUP
#define INCLUDE_UTILITIES_LOOKUP

#include "Common.h"
#include "LinkedList.h"

typedef void (*Lookup_ElementDisposer)(void*);

typedef struct {
	uint64 Key;
	void* Value;
} Lookup_Entry;

typedef struct {
	LinkedList Entries;
} Lookup;

#define Lookup_Find(lookup, key, type) ((type)Lookup_FindValue((lookup), key))

public Lookup* Lookup_New(Lookup_ElementDisposer elementDisposer);
public void Lookup_Initialize(Lookup* lookup, Lookup_ElementDisposer elementDisposer);
public void Lookup_Free(Lookup* self);
public void Lookup_Uninitialize(Lookup* self);
public boolean Lookup_Add(Lookup* self, uint64 key, void* value, boolean overwrite);
public void* Lookup_FindValue(Lookup* self, uint64 key);
public Lookup_Entry* Lookup_FindEntry(Lookup* self, uint64 key);
public boolean Lookup_Remove(Lookup* self, uint64 key);
public void Lookup_Clear(Lookup* self);

#endif
