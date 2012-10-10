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

public LinkedList* LinkedList_New(NodeDataDisposer itemDisposer);
public void LinkedList_Initialize(LinkedList* list, NodeDataDisposer itemDisposer);
public void LinkedList_Dispose(LinkedList* self);

public Node* LinkedList_FindNode(LinkedList* self, void* toFind);
public void LinkedList_ResetIterator(LinkedList* self);
public void* LinkedList_Iterate(LinkedList* self);

public void LinkedList_Remove(LinkedList* self, void* data);
public void LinkedList_RemoveNode(LinkedList* self, Node* node);
public void LinkedList_Prepend(LinkedList* self, void* data);
public void LinkedList_Append(LinkedList* self, void* data);
public void LinkedList_Insert(LinkedList* self, void* data);

#endif
