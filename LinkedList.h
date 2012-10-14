#ifndef INCLUDE_UTILITIES_LINKEDLIST
#define INCLUDE_UTILITIES_LINKEDLIST

#include "Common.h"

typedef void (*NodeDataDisposer)(void*);

typedef struct _Node {
	void* Data;
	struct _Node* Prev;
	struct _Node* Next;
} Node;

typedef struct {
	Node* First;
	Node* Last;
	Node* Current;
	uint64 Count;
	NodeDataDisposer Disposer;
} LinkedList;

typedef struct {
    LinkedList* List;
    Node* Position;
    uint64 Index;
} LinkedList_Iterator;

#define LinkedList_ForEach(current, iterator, type) LinkedList_ResetIterator(iterator); while ((current = (type*)LinkedList_Iterate(iterator)) != NULL)
#define LinkedList_IterateNext(current, iterator, type) current = (type*)LinkedList_Iterate(iterator)

/* iterates from the current location in the list, does not reset the pointer to the beginning */
#define LinkedList_ForCurrent(current, iterator, type) while ((current = (type*)LinkedList_Iterate(iterator)) != NULL)

public LinkedList* LinkedList_New(NodeDataDisposer itemDisposer);
public void LinkedList_Initialize(LinkedList* list, NodeDataDisposer itemDisposer);
public void LinkedList_Free(LinkedList* self);

public Node* LinkedList_FindNode(LinkedList* self, void* toFind);
public void* LinkedList_Iterate(LinkedList_Iterator* iterator);
public LinkedList_Iterator* LinkedList_BeginIterate(LinkedList* self);
public void LinkedList_EndIterate(LinkedList_Iterator* iterator);
public void LinkedList_ResetIterator(LinkedList_Iterator* iterator);

public void LinkedList_Remove(LinkedList* self, void* data);
public void LinkedList_RemoveNode(LinkedList* self, Node* node);
public void LinkedList_Prepend(LinkedList* self, void* data);
public void LinkedList_Append(LinkedList* self, void* data);
public void LinkedList_Insert(LinkedList* self, void* data);

#endif
