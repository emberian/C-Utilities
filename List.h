#ifndef INCLUDE_UTILITIES_LIST
#define INCLUDE_UTILITIES_LIST

#include "Common.h"
#include "Array.h"

typedef void (*List_ElementDisposer)(void*);

/* forward declarations */
struct List;
struct List_Iterator;

typedef struct List {
	Array DataStore;
	uint64 Cursor;
	uint64 Count;
	struct List_Iterator* DefaultIterator;
	List_ElementDisposer Disposer;
} List;

typedef struct List_Iterator {
    struct List* ParentList;
    uint64 Position;
} List_Iterator;


/* Iterates over every item in list using the list's DefaultIterator method. Resets the iterator upon invocation. Used like a while loop. */ 
#define List_ForEach(current, list, type) List_ResetIterator((list)->DefaultIterator); while ((current) = (type)List_Iterate((list)->DefaultIterator))

/* Returns the next item in the list and advances the iteration pointer. Accepts a type to cast the returned value for you. */
#define List_IterateNext(current, iterator, type) ((current) = (type*)List_Iterate(iterator))

public List* List_New(List_ElementDisposer elementDisposer);
public void List_Initialize(List* list, List_ElementDisposer elementDisposer);
public void List_Free(List* self);
public void List_Uninitialize(List* self);

public void List_Append(List* self, void* data);

public void* List_Iterate(List_Iterator* iterator);
public List_Iterator* List_BeginIterate(List* self);
public void List_EndIterate(List_Iterator* iterator);
public void List_ResetIterator(List_Iterator* iterator);

#endif
