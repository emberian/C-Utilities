#include "AsyncLinkedList.h"

AsyncLinkedList* AsyncLinkedList_New(LinkedList_ElementDisposer elementDisposer) {
    AsyncLinkedList* list;

    list = Allocate(AsyncLinkedList);
    AsyncLinkedList_Initialize(list, elementDisposer);

    return list;
}

void AsyncLinkedList_Initialize(AsyncLinkedList* list, LinkedList_ElementDisposer elementDisposer) {
    assert(list != NULL);
    
    list->BaseList = LinkedList_New(elementDisposer);
    list->Lock = SAL_Mutex_Create();
    list->DefaultIterator = Allocate(AsyncLinkedList_Iterator);
    AsyncLinkedList_InitializeIterator(list->DefaultIterator, list);
}

void AsyncLinkedList_Free(AsyncLinkedList* self) {
    AsyncLinkedList_Uninitialize(self);

    Free(self);
}

void AsyncLinkedList_Uninitialize(AsyncLinkedList* self) {
    assert(self != NULL);
    
    LinkedList_Free(self->BaseList);
    SAL_Mutex_Free(self->Lock);
    Free(self->DefaultIterator);
}

void* AsyncLinkedList_FindValue(AsyncLinkedList* self, void* toFind) {
    void* result;
    
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    result = LinkedList_FindValue(self->BaseList, toFind);
    SAL_Mutex_Release(self->Lock);

    return result;
}

Node* AsyncLinkedList_FindNode(AsyncLinkedList* self, void* toFind) {
    Node* result;
    
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    result = LinkedList_FindNode(self->BaseList, toFind);
    SAL_Mutex_Release(self->Lock);

    return result;
}

uint64 AsyncLinkedList_GetCount(AsyncLinkedList* self) {
    uint64 result;

    assert(self != NULL);
    
    SAL_Mutex_Acquire(self->Lock);
    result = self->BaseList->Count;
    SAL_Mutex_Release(self->Lock);

    return result;
}

void* AsyncLinkedList_Iterate(AsyncLinkedList_Iterator* iterator) {
    void* result;

    assert(iterator != NULL);
    
    SAL_Mutex_Acquire(iterator->BaseList->Lock);
    result = LinkedList_Iterate(&iterator->BaseIterator);
    SAL_Mutex_Release(iterator->BaseList->Lock);

    return result;
}

void AsyncLinkedList_InitializeIterator(AsyncLinkedList_Iterator* iterator, AsyncLinkedList* list) {
    assert(iterator != NULL);
    assert(list != NULL);
    
    SAL_Mutex_Acquire(list->Lock);
    iterator->BaseList = list;
    LinkedList_InitializeIterator(&iterator->BaseIterator, list->BaseList);
    SAL_Mutex_Release(list->Lock);
}

void AsyncLinkedList_ResetIterator(AsyncLinkedList_Iterator* iterator) {
    assert(iterator != NULL);
    
    SAL_Mutex_Acquire(iterator->BaseList->Lock);
    LinkedList_ResetIterator(&iterator->BaseIterator);
    SAL_Mutex_Release(iterator->BaseList->Lock);
}

void AsyncLinkedList_Clear(AsyncLinkedList* self) {
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    LinkedList_Clear(self->BaseList);
    SAL_Mutex_Release(self->Lock);
}

void AsyncLinkedList_Remove(AsyncLinkedList* self, void* data) {
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    LinkedList_Remove(self->BaseList, data);
    SAL_Mutex_Release(self->Lock);
}

void AsyncLinkedList_RemoveNode(AsyncLinkedList* self, Node* node) {
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    LinkedList_RemoveNode(self->BaseList, node);
    SAL_Mutex_Release(self->Lock);
}

void AsyncLinkedList_Prepend(AsyncLinkedList* self, void* data) {
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    LinkedList_Prepend(self->BaseList, data);
    SAL_Mutex_Release(self->Lock);
}

void AsyncLinkedList_Append(AsyncLinkedList* self, void* data) {
    assert(self != NULL);

    SAL_Mutex_Acquire(self->Lock);
    LinkedList_Append(self->BaseList, data);
    SAL_Mutex_Release(self->Lock);
}

void AsyncLinkedList_Insert(AsyncLinkedList_Iterator* iterator, void* data) {
    assert(iterator != NULL);

    SAL_Mutex_Acquire(iterator->BaseList->Lock);
    LinkedList_Insert(&iterator->BaseIterator, data);
    SAL_Mutex_Release(iterator->BaseList->Lock);
}
