#include "LinkedList.h"

LinkedList* LinkedList_New(NodeDataDisposer itemDisposer) {
	LinkedList* list;

	list = Allocate(LinkedList);
	LinkedList_Initialize(list, itemDisposer);

	return list;
}

void LinkedList_Initialize(LinkedList* list, NodeDataDisposer itemDisposer) {
    assert(list != NULL);

    if (itemDisposer == NULL) itemDisposer = free;

    list->Count = 0;
    list->First = NULL;
    list->Last = NULL;
    list->Current = NULL;
    list->Disposer = itemDisposer;
}

void LinkedList_Dispose(LinkedList* self) {
    assert(self != NULL);

	while (self->First != NULL) {
		if (self->Disposer)
			self->Disposer(self->First->Data);

		self->First = self->First->Next;
		Free(self->First->Prev);
	}

    self->Count = 0;
    self->Current = NULL;
    self->Disposer = NULL;
    self->First = NULL;
    self->Last = NULL;
	
	Free(self);
}

Node* LinkedList_FindNode(LinkedList* self, void* toFind) {
	Node* current;
	
	current = NULL;
	current = self->First;

	while (current != NULL) {
		if (current->Data == toFind)
			break;

		current = current->Next;
	}

	self->Current = self->First;

	return current;
}

void LinkedList_ResetIterator(LinkedList* self) {
	assert(self != NULL);
	
	self->Current = self->First;
}

void* LinkedList_Iterate(LinkedList* self) {
	void* data;
	
	assert(self != NULL);
	
	data = NULL;

	if (self->Current) {
		data = self->Current->Data;
        self->Current = self->Current->Next;
	}

	return data;
}

void LinkedList_Remove(LinkedList* self, void* data) {
	Node* node;
	
	assert(self != NULL && data != NULL);

	node = LinkedList_FindNode(self, data);

	if (node)
        LinkedList_RemoveNode(self, node);
}

void LinkedList_RemoveNode(LinkedList* self, Node* node) {
	assert(self != NULL && node != NULL);

	if (self->First == NULL)
		return;

	if (node == NULL)
		return;

	if (self->First == self->Last) {
		self->First = NULL;
		self->Last = NULL;
		self->Current = NULL;
	}
	else if (self->First == node) {
		self->First = node->Next;
		self->First->Prev = NULL;

		if (self->Current == node)
			self->Current = self->First;
	}
	else if (self->Last == node) {
		self->Last = node->Prev;
		self->Last->Next = NULL;

		if (self->Current == node)
			self->Current = self->Last;
	}
	else {
		node->Prev->Next = node->Next;
		node->Next->Prev = node->Prev;
	}

	if (self->Disposer)
		self->Disposer(node->Data);

	node->Data = NULL;
	node->Prev = NULL;
	node->Next = NULL;
	Free(node);

	self->Count--;
}

void LinkedList_Prepend(LinkedList* self, void* data) {
	Node* node;

	assert(self != NULL && data != NULL);
  
	node = Allocate(Node);
	node->Data = data;
	node->Prev = NULL;

	if (self->First != NULL) {
		node->Next = self->First;
		self->First->Prev = node;
		self->First = node;
	}
	else {
		node->Next = NULL;
		self->First = node;
		self->Last = node;
		self->Current = node;
	}

	self->Count++;
}            

void LinkedList_Append(LinkedList* self, void* data) {
	Node* node;
	
	assert(self != NULL && data != NULL);
	
	node = Allocate(Node);
	node->Data = data;
	node->Next = NULL;

	if (self->Last != NULL) {
		node->Prev = self->Last;
		self->Last->Next = node;
		self->Last = node;
	}
	else {
		node->Prev = NULL;
		self->First = node;
		self->Last = node;
		self->Current = node;
	}

	self->Count++;
}

void LinkedList_Insert(LinkedList* self, void* data) {
	Node* node;

	assert(self != NULL && data != NULL);
  
	if (self->Current == NULL) {
		LinkedList_Append(self, data);
	}
	else {
		node = Allocate(Node);
		node->Data = data;

		node->Prev = self->Current;
		node->Next = self->Current->Next;
		self->Current->Next->Prev = node;
		self->Current->Next = node;
		self->Current = node;
	}

	self->Count++;
}
