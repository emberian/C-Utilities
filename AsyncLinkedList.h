#ifndef INCLUDE_UTILITIES_ASYNCLINKEDLIST
#define INCLUDE_UTILITIES_ASYNCLINKEDLIST

#include "Common.h"
#include "LinkedList.h"
#include <SAL/Thread.h>

/* forward declarations */
struct AsyncLinkedList;
struct AsyncLinkedList_Iterator;

typedef struct AsyncLinkedList {
	LinkedList* BaseList;
	SAL_Mutex Lock;
} AsyncLinkedList;

typedef struct AsyncLinkedList_Iterator {
    struct AsyncLinkedList* ParentList;
	LinkedList_Iterator* BaseIterator;
} AsyncLinkedList_Iterator;

/* Iterates over every item in list using the list's DefaultIterator method. Resets the iterator upon invocation. Used like a while loop. */
#define AsyncLinkedList_ForEach(current, list, type) AsyncLinkedList_ResetIterator((list)->BaseList->DefaultIterator); while ((current) = (type)AsyncLinkedList_Iterate((list)->BaseList->DefaultIterator))

/* Returns the next item in the list and advances the iteration pointer. Accepts a type to cast the returned value for you. */
#define AsyncLinkedList_IterateNext(current, iterator, type) ((current) = (type)AsyncLinkedList_Iterate(iterator))

#define AsyncLinkedList_Find(list, value, type) ((type)AsyncLinkedList_FindValue((list), (value)))

public AsyncLinkedList* AsyncLinkedList_New(LinkedList_ElementDisposer itemDisposer);
public void AsyncLinkedList_Initialize(AsyncLinkedList* list, LinkedList_ElementDisposer itemDisposer);
public void AsyncLinkedList_Free(AsyncLinkedList* self);
public void AsyncLinkedList_Uninitialize(AsyncLinkedList* self);

public void* AsyncLinkedList_FindValue(AsyncLinkedList* self, void* toFind);
public Node* AsyncLinkedList_FindNode(AsyncLinkedList* self, void* toFind);
public void* AsyncLinkedList_Iterate(AsyncLinkedList_Iterator* iterator);
public AsyncLinkedList_Iterator* AsyncLinkedList_BeginIterate(AsyncLinkedList* self);
public void AsyncLinkedList_EndIterate(AsyncLinkedList_Iterator* iterator);
public void AsyncLinkedList_ResetIterator(AsyncLinkedList_Iterator* iterator);

public void AsyncLinkedList_Clear(AsyncLinkedList* self);
public void AsyncLinkedList_Remove(AsyncLinkedList* self, void* data);
public void AsyncLinkedList_RemoveNode(AsyncLinkedList* self, Node* node);
public void AsyncLinkedList_Prepend(AsyncLinkedList* self, void* data);
public void AsyncLinkedList_Append(AsyncLinkedList* self, void* data);
public void AsyncLinkedList_Insert(AsyncLinkedList_Iterator* iterator, void* data);

#endif
