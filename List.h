#ifndef INCLUDE_UTILITIES_LIST
#define INCLUDE_UTILITIES_LIST

#include "Common.h"
#include "Array.h"

typedef void (*List_ElementDisposer)(void*);

/* forward declarations */
typedef struct List List;
typedef struct List_Iterator List_Iterator;

struct List {
	Array DataStore;
	uint64 Cursor;
	uint64 Count;
	List_Iterator* DefaultIterator;
	List_ElementDisposer Disposer;
};

struct List_Iterator {
    List* ParentList;
    uint64 Position;
};

/* Iterates over every item in list using the list's DefaultIterator method. Resets the iterator upon invocation. Used like a while loop. */ 
#define List_ForEach(current, list, type) List_ResetIterator((list)->DefaultIterator); while ((current) = (type)List_Iterate((list)->DefaultIterator))

export List* List_New(List_ElementDisposer elementDisposer);
export void List_Initialize(List* list, List_ElementDisposer elementDisposer);
export void List_Free(List* self);
export void List_Uninitialize(List* self);

export void List_Append(List* self, void* data);

export void* List_Iterate(List_Iterator* iterator);
export void List_InitializeIterator(List_Iterator* iterator, List* list);
export void List_ResetIterator(List_Iterator* iterator);

#endif
