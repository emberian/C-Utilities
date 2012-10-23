#ifndef INCLUDE_UTILITIES_ASYNCLIST
#define INCLUDE_UTILITIES_ASYNCLIST

#include "Common.h"
#include "List.h"
#include <SAL/Thread.h>

/* forward declarations */
struct AsyncList;
struct AsyncList_Iterator;

typedef struct AsyncList {
	List* BaseList;
	SAL_Mutex Lock;
	struct AsyncList_Iterator* DefaultIterator;
} AsyncList;

typedef struct AsyncList_Iterator {
    struct AsyncList* ParentList;
	List_Iterator* BaseIterator;
} AsyncList_Iterator;


/* Iterates over every item in list using the list's DefaultIterator method. Resets the iterator upon invocation. Used like a while loop. */ 
#define AsyncList_ForEach(current, list, type) AsyncList_ResetIterator((list)->DefaultIterator); while ((current) = (type)AsyncList_Iterate((list)->DefaultIterator))

/* Returns the next item in the list and advances the iteration pointer. Accepts a type to cast the returned value for you. */
#define AsyncList_IterateNext(current, iterator, type) ((current) = (type)AsyncList_Iterate(iterator))

public AsyncList* AsyncList_New(List_ElementDisposer elementDisposer);
public void AsyncList_Initialize(AsyncList* list, List_ElementDisposer elementDisposer);
public void AsyncList_Free(AsyncList* self);
public void AsyncList_Uninitialize(AsyncList* self);

public void AsyncList_Append(AsyncList* self, void* data);

public void* AsyncList_Iterate(AsyncList_Iterator* iterator);
public AsyncList_Iterator* AsyncList_BeginIterate(AsyncList* self);
public void AsyncList_EndIterate(AsyncList_Iterator* iterator);
public void AsyncList_ResetIterator(AsyncList_Iterator* iterator);

#endif
