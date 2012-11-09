#include "List.h"
#include "Memory.h"

List* List_New(List_ElementDisposer elementDisposer) {
	List* list;

	list = Allocate(List);
	List_Initialize(list, elementDisposer);

	return list;
}

void List_Initialize(List* list, List_ElementDisposer elementDisposer) {
	assert(list != NULL);

	list->Cursor = 0;
	list->Count = 0;
	list->Disposer = elementDisposer;
	list->DefaultIterator = Allocate(List_Iterator);
	List_InitializeIterator(list->DefaultIterator, list);
	Array_Initialize(&list->DataStore, 64);
}

void List_Free(List* self) {
	List_Uninitialize(self);
	
	Free(self);
}

void List_Uninitialize(List* self) {
	void* current;

	assert(self != NULL);

	if (self->Disposer) {
		List_ResetIterator(self->DefaultIterator);
		while (current = List_Iterate(self->DefaultIterator))
			self->Disposer(current);
	}
	
	self->Count = 0;
	self->Cursor = 0;
	self->Disposer = NULL;
	Free(self->DefaultIterator);
	Array_Uninitialize(&self->DataStore);
}

void List_Append(List* self, void* data) {
	uint64 address;

	assert(self != NULL && data != NULL);
	
	address = (uint64)data;

	Array_Write(&self->DataStore, (uint8*)&address, self->Count * sizeof(void*), sizeof(void*));

	self->Count++;
}

void* List_Iterate(List_Iterator* iterator) {
	uint64 data;
	void* address;

	assert(iterator != NULL);
	
	address = NULL;

	if (iterator->Position < iterator->ParentList->Count) {
		data = *(uint64*)Array_Read(&iterator->ParentList->DataStore, iterator->Position * sizeof(void*), sizeof(void*));
		address = (void*)data;
		iterator->Position++;
	}

	return address;
}

void List_InitializeIterator(List_Iterator* iterator, List* list) {
	assert(iterator != NULL);
	assert(list != NULL);

	iterator->Position = 0;
	iterator->ParentList = list;
}

void List_ResetIterator(List_Iterator* iterator) {
	assert(iterator != NULL);
	
	iterator->Position = 0;
}
