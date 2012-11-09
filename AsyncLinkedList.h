#ifndef INCLUDE_UTILITIES_ASYNCLINKEDLIST
#define INCLUDE_UTILITIES_ASYNCLINKEDLIST

#include "Common.h"
#include "LinkedList.h"
#include <SAL/Thread.h>

/* forward declarations */
typedef struct AsyncLinkedList AsyncLinkedList;
typedef struct AsyncLinkedList_Iterator AsyncLinkedList_Iterator;

struct AsyncLinkedList {
	LinkedList* BaseList;
	SAL_Mutex Lock;
	AsyncLinkedList_Iterator* DefaultIterator;
};

struct AsyncLinkedList_Iterator {
	AsyncLinkedList* BaseList;
	LinkedList_Iterator BaseIterator;
};

/* Iterates over every item in list using the list's DefaultIterator method. Resets the iterator upon invocation. Used like a while loop. */
#define AsyncLinkedList_ForEach(current, list, type) AsyncLinkedList_ResetIterator((list)->DefaultIterator); while ((current) = (type)AsyncLinkedList_Iterate((list)->DefaultIterator))

public AsyncLinkedList* AsyncLinkedList_New(LinkedList_ElementDisposer itemDisposer);
public void AsyncLinkedList_Initialize(AsyncLinkedList* list, LinkedList_ElementDisposer itemDisposer);
public void AsyncLinkedList_Free(AsyncLinkedList* self);
public void AsyncLinkedList_Uninitialize(AsyncLinkedList* self);

public void* AsyncLinkedList_FindValue(AsyncLinkedList* self, void* toFind);
public Node* AsyncLinkedList_FindNode(AsyncLinkedList* self, void* toFind);
public uint64 AsyncLinkedList_GetCount(AsyncLinkedList* self);

public void* AsyncLinkedList_Iterate(AsyncLinkedList_Iterator* iterator);
public void AsyncLinkedList_InitializeIterator(AsyncLinkedList_Iterator* iterator, AsyncLinkedList* list);
public void AsyncLinkedList_ResetIterator(AsyncLinkedList_Iterator* iterator);

public void AsyncLinkedList_Clear(AsyncLinkedList* self);
public void AsyncLinkedList_Remove(AsyncLinkedList* self, void* data);
public void AsyncLinkedList_RemoveNode(AsyncLinkedList* self, Node* node);
public void AsyncLinkedList_Prepend(AsyncLinkedList* self, void* data);
public void AsyncLinkedList_Append(AsyncLinkedList* self, void* data);
public void AsyncLinkedList_Insert(AsyncLinkedList_Iterator* iterator, void* data);

#endif
