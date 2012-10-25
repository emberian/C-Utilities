#ifndef INCLUDE_UTILITIES_LINKEDLIST
#define INCLUDE_UTILITIES_LINKEDLIST

#include "Common.h"

typedef void (*LinkedList_ElementDisposer)(void*);

/* forward declarations */
typedef struct Node Node;
typedef struct LinkedList LinkedList;
typedef struct LinkedList_Iterator LinkedList_Iterator;

struct Node {
	void* Data;
	Node* Prev;
	Node* Next;
};

struct LinkedList {
	Node* First;
	Node* Last;
	LinkedList_Iterator* DefaultIterator; /* An iterator managed by the List itself for use by the user. Warning: a call to ForEach resets this iterator. */
	uint64 Count;
	LinkedList_ElementDisposer Disposer;
};

struct LinkedList_Iterator {
	LinkedList* List;
	Node* Position;
	uint64 Index;
};

/* Iterates over every item in list using the list's DefaultIterator method. Resets the iterator upon invocation. Used like a while loop. */
#define LinkedList_ForEach(current, list, type) LinkedList_ResetIterator((list)->DefaultIterator); while ((current) = (type)LinkedList_Iterate((list)->DefaultIterator))

public LinkedList* LinkedList_New(LinkedList_ElementDisposer itemDisposer);
public void LinkedList_Initialize(LinkedList* list, LinkedList_ElementDisposer itemDisposer);
public void LinkedList_Free(LinkedList* self);
public void LinkedList_Uninitialize(LinkedList* self);

public void* LinkedList_FindValue(LinkedList* self, void* toFind);
public Node* LinkedList_FindNode(LinkedList* self, void* toFind);

public void* LinkedList_Iterate(LinkedList_Iterator* iterator);
public void LinkedList_InitializeIterator(LinkedList_Iterator* iterator, LinkedList* list);
public void LinkedList_ResetIterator(LinkedList_Iterator* iterator);

public void LinkedList_Clear(LinkedList* self);
public void LinkedList_Remove(LinkedList* self, void* data);
public void LinkedList_RemoveNode(LinkedList* self, Node* node);
public void LinkedList_Prepend(LinkedList* self, void* data);
public void LinkedList_Append(LinkedList* self, void* data);
public void LinkedList_Insert(LinkedList_Iterator* iterator, void* data);

#endif
