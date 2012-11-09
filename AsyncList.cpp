#include "AsyncList.h"
#include "Memory.h"

AsyncList* AsyncList_New(List_ElementDisposer elementDisposer) {
	AsyncList* list;

	list = Allocate(AsyncList);
	AsyncList_Initialize(list, elementDisposer);

	return list;
}

void AsyncList_Initialize(AsyncList* list, List_ElementDisposer elementDisposer) {
	assert(list != NULL);

	list->BaseList = List_New(elementDisposer);
	list->Lock = SAL_Mutex_Create();
	list->DefaultIterator = Allocate(AsyncList_Iterator);
	AsyncList_InitializeIterator(list->DefaultIterator, list);
}

void AsyncList_Free(AsyncList* self) {
	AsyncList_Uninitialize(self);
	
	Free(self);
}

void AsyncList_Uninitialize(AsyncList* self) {
	assert(self != NULL);

	List_Free(self->BaseList);
	SAL_Mutex_Free(self->Lock);
	Free(self->DefaultIterator);
}

void AsyncList_Append(AsyncList* self, void* data) {
	assert(self != NULL && data != NULL);
	
	SAL_Mutex_Acquire(self->Lock);
	List_Append(self->BaseList, data);
	SAL_Mutex_Release(self->Lock);
}

uint64 AsyncList_GetCount(AsyncList* self) {
	uint64 result;

	assert(self != NULL);
	
	SAL_Mutex_Acquire(self->Lock);
	result = self->BaseList->Count;
	SAL_Mutex_Release(self->Lock);

	return result;
}

void* AsyncList_Iterate(AsyncList_Iterator* iterator) {
	void* result;

	assert(iterator != NULL);
	
	SAL_Mutex_Acquire(iterator->BaseList->Lock);
	result = List_Iterate(&iterator->BaseIterator);
	SAL_Mutex_Release(iterator->BaseList->Lock);

	return result;
}

void AsyncList_InitializeIterator(AsyncList_Iterator* iterator, AsyncList* list) {
	assert(iterator != NULL);
	assert(list != NULL);
	
	SAL_Mutex_Acquire(list->Lock);
	iterator->BaseList = list;
	List_InitializeIterator(&iterator->BaseIterator, list->BaseList);
	SAL_Mutex_Release(list->Lock);
}

void AsyncList_ResetIterator(AsyncList_Iterator* iterator) {
	assert(iterator != NULL);
	
	SAL_Mutex_Acquire(iterator->BaseList->Lock);
	List_ResetIterator(&iterator->BaseIterator);
	SAL_Mutex_Release(iterator->BaseList->Lock);
}
