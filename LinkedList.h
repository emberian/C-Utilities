#ifndef INCLUDE_UTILITIES_LINKEDLIST
#define INCLUDE_UTILITIES_LINKEDLIST

#include "Common.h"

typedef void (*NodeDataDisposer)(void*);

/* forward declarations */
struct Node;
struct LinkedList;
struct LinkedList_Iterator;

typedef struct Node {
	void* Data;
	struct Node* Prev;
	struct Node* Next;
} Node;

typedef struct LinkedList {
	Node* First;
	Node* Last;
	struct LinkedList_Iterator* DefaultIterator;
	uint64 Count;
	NodeDataDisposer Disposer;
} LinkedList;

typedef struct LinkedList_Iterator {
    LinkedList* List;
    Node* Position;
    uint64 Index;
} LinkedList_Iterator;

#define LinkedList_ForEach(current, list, type) LinkedList_ResetIterator((list)->DefaultIterator); while (current = (type*)LinkedList_Iterate((list)->DefaultIterator))
#define LinkedList_IterateNext(current, iterator, type) (current = (type*)LinkedList_Iterate(iterator))

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
public void LinkedList_Insert(LinkedList_Iterator* iterator, void* data);

#endif
