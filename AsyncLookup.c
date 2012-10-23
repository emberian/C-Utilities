#include "AsyncLookup.h"

AsyncLookup* AsyncLookup_New(Lookup_ElementDisposer elementDisposer) {
	AsyncLookup* lookup;

	lookup = Allocate(AsyncLookup);
	AsyncLookup_Initialize(lookup, elementDisposer);

	return lookup;
}

void AsyncLookup_Initialize(AsyncLookup* lookup, Lookup_ElementDisposer elementDisposer) {
    assert(lookup != NULL);

	lookup->BaseLookup = Lookup_New(elementDisposer);
	lookup->Lock = SAL_Mutex_Create();
}

void AsyncLookup_Free(AsyncLookup* self) {
    AsyncLookup_Uninitialize(self);
	
	Free(self);
}

void AsyncLookup_Uninitialize(AsyncLookup* self) {
    assert(self != NULL);

	Lookup_Free(self->BaseLookup);
	SAL_Mutex_Free(self->Lock);
}

boolean AsyncLookup_Add(AsyncLookup* self, void* key, void* value, boolean overwrite) {
	boolean result;

	SAL_Mutex_Acquire(self->Lock);
	result = Lookup_Add(self->BaseLookup, key, value, overwrite);
	SAL_Mutex_Free(self->Lock);
	
	return result;
}

void* AsyncLookup_FindValue(AsyncLookup* self, void* key) {
	void* result;

	SAL_Mutex_Acquire(self->Lock);
	result = Lookup_FindValue(self->BaseLookup, key);
	SAL_Mutex_Free(self->Lock);
	
	return result;
}

Lookup_Entry* AsyncLookup_FindEntry(AsyncLookup* self, void* key) {
	Lookup_Entry* result;

	SAL_Mutex_Acquire(self->Lock);
	result = Lookup_FindEntry(self->BaseLookup, key);
	SAL_Mutex_Free(self->Lock);
	
	return result;
}

boolean AsyncLookup_Remove(AsyncLookup* self, void* key) {
	boolean result;

	SAL_Mutex_Acquire(self->Lock);
	result = Lookup_Remove(self->BaseLookup, key);
	SAL_Mutex_Free(self->Lock);
	
	return result;
}

void AsyncLookup_Clear(AsyncLookup* self) {
	SAL_Mutex_Acquire(self->Lock);
	Lookup_Clear(self->BaseLookup);
	SAL_Mutex_Free(self->Lock);
}