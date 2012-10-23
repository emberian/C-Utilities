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
	list->DefaultIterator = AsyncList_BeginIterate(list);
}

void AsyncList_Free(AsyncList* self) {
    AsyncList_Uninitialize(self);
	
	Free(self);
}

void AsyncList_Uninitialize(AsyncList* self) {
    assert(self != NULL);

	List_Free(self->BaseList);
	SAL_Mutex_Free(self->Lock);
	AsyncList_EndIterate(self->DefaultIterator);
}

void AsyncList_Append(AsyncList* self, void* data) {
	assert(self != NULL && data != NULL);
	
	SAL_Mutex_Acquire(self->Lock);
	List_Append(self->BaseList, data);
	SAL_Mutex_Free(self->Lock);
}

void* AsyncList_Iterate(AsyncList_Iterator* iterator) {
	void* result;

	assert(iterator != NULL);
	
	SAL_Mutex_Acquire(iterator->ParentList->Lock);
	result = List_Iterate(iterator->BaseIterator);
	SAL_Mutex_Release(iterator->ParentList->Lock);

	return result;
}

AsyncList_Iterator* AsyncList_BeginIterate(AsyncList* self) {
    AsyncList_Iterator* iterator;

	assert(self != NULL);
	
	SAL_Mutex_Acquire(self->Lock);
    iterator = Allocate(AsyncList_Iterator);
    iterator->ParentList = self;
    iterator->BaseIterator = List_BeginIterate(self->BaseList);
	SAL_Mutex_Release(self->Lock);

    return iterator;
}

void AsyncList_EndIterate(AsyncList_Iterator* iterator) {
	assert(iterator != NULL);
	
	SAL_Mutex_Acquire(iterator->ParentList->Lock);
	List_EndIterate(iterator->BaseIterator);
	SAL_Mutex_Release(iterator->ParentList->Lock);
	iterator->BaseIterator = NULL;
	iterator->ParentList = NULL;

    Free(iterator);
}

void AsyncList_ResetIterator(AsyncList_Iterator* iterator) {
	assert(iterator != NULL);
	
	SAL_Mutex_Acquire(iterator->ParentList->Lock);
	List_ResetIterator(iterator->BaseIterator);
	SAL_Mutex_Release(iterator->ParentList->Lock);
}
