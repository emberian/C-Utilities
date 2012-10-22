#include "Lookup.h"

Lookup* Lookup_New(Lookup_ElementDisposer elementDisposer) {
	Lookup* lookup;

	lookup = Allocate(Lookup);
	Lookup_Initialize(lookup, elementDisposer);

	return lookup;
}

void Lookup_Initialize(Lookup* lookup, Lookup_ElementDisposer elementDisposer) {
    assert(lookup != NULL);

	LinkedList_Initialize(&lookup->Entries, elementDisposer);
}

void Lookup_Free(Lookup* self) {
    Lookup_Uninitialize(self);
	
	Free(self);
}

void Lookup_Uninitialize(Lookup* self) {
    assert(self != NULL);

	LinkedList_Uninitialize(&self->Entries);
}

boolean Lookup_Add(Lookup* self, void* key, void* value, boolean overwrite) {
	Lookup_Entry* current;

	if (current = Lookup_FindEntry(self, key)) {
		if (overwrite)
			current->Value = value;
		else 
			return false;
	}
	else {
		current = Allocate(Lookup_Entry);
		current->Key = key;
		current->Value = value;
		LinkedList_Append(&self->Entries, current);
	}
	
	return true;
}

void* Lookup_FindValue(Lookup* self, void* key) {
	Lookup_Entry* current;

	LinkedList_ForEach(current, &self->Entries, Lookup_Entry*)
		if (current->Key == key)
			return current->Value;

	return NULL;
}

Lookup_Entry* Lookup_FindEntry(Lookup* self, void* key) {
	Lookup_Entry* current;

	LinkedList_ForEach(current, &self->Entries, Lookup_Entry*)
		if (current->Key == key)
			return current;

	return NULL;
}

boolean Lookup_Remove(Lookup* self, void* key) {
	Lookup_Entry* current;

	if (current = Lookup_FindEntry(self, key)) {
		LinkedList_Remove(&self->Entries, current);
		return true;
	}
	
	return false;
}

void Lookup_Clear(Lookup* self) {
	LinkedList_Clear(&self->Entries);
}