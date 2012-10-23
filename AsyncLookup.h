#ifndef INCLUDE_UTILITIES_ASYNCLOOKUP
#define INCLUDE_UTILITIES_ASYNCLOOKUP

#include "Common.h"
#include "LinkedList.h"
#include "Lookup.h"
#include <SAL/Thread.h>

typedef struct {
	Lookup* BaseLookup;
	SAL_Mutex Lock;
} AsyncLookup;

#define AsyncLookup_Find(lookup, key, type) ((type)AsyncLookup_FindValue((lookup), (key)))

public AsyncLookup* AsyncLookup_New(Lookup_ElementDisposer elementDisposer);
public void AsyncLookup_Initialize(AsyncLookup* lookup, Lookup_ElementDisposer elementDisposer);
public void AsyncLookup_Free(AsyncLookup* self);
public void AsyncLookup_Uninitialize(AsyncLookup* self);
public boolean AsyncLookup_Add(AsyncLookup* self, void* key, void* value, boolean overwrite);
public void* AsyncLookup_FindValue(AsyncLookup* self, void* key);
public Lookup_Entry* AsyncLookup_FindEntry(AsyncLookup* self, void* key);
public boolean AsyncLookup_Remove(AsyncLookup* self, void* key);
public void AsyncLookup_Clear(AsyncLookup* self);

#endif
