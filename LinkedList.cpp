#include "LinkedList.h"
#include "Memory.h"

LinkedList* LinkedList_New(LinkedList_ElementDisposer elementDisposer) {
	LinkedList* list;

	list = Allocate(LinkedList);
	LinkedList_Initialize(list, elementDisposer);

	return list;
}

void LinkedList_Initialize(LinkedList* list, LinkedList_ElementDisposer elementDisposer) {
	assert(list != NULL);

	list->Count = 0;
	list->First = NULL;
	list->Last = NULL;
	list->Disposer = elementDisposer;
	list->DefaultIterator = Allocate(LinkedList_Iterator);
	LinkedList_InitializeIterator(list->DefaultIterator, list);
}

void LinkedList_Free(LinkedList* self) {
	LinkedList_Uninitialize(self);

	Free(self);
}

void LinkedList_Uninitialize(LinkedList* self) {
	Node* prior;

	assert(self != NULL);

	while (self->First != NULL) {
		if (self->Disposer)
			self->Disposer(self->First->Data);

		prior = self->First;
		self->First = self->First->Next;
		Free(prior);
	}

	self->Count = 0;
	self->Disposer = NULL;
	self->First = NULL;
	self->Last = NULL;
	Free(self->DefaultIterator);
}

void* LinkedList_FindValue(LinkedList* self, void* toFind) {
	Node* current;

	current = NULL;
	current = self->First;

	while (current != NULL) {
		if (current->Data == toFind)
			break;

		current = current->Next;
	}

	return current != NULL ? current->Data : NULL;
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

	return current;
}

void* LinkedList_Iterate(LinkedList_Iterator* iterator) {
	void* data;

	assert(iterator != NULL);

	data = NULL;

	if (iterator->Position && iterator->List->Count != 0) {
		data = iterator->Position->Data;
		iterator->Position = iterator->Position->Next;
		iterator->Index++;
	}

	return data;
}

void LinkedList_InitializeIterator(LinkedList_Iterator* iterator, LinkedList* list) {
	assert(iterator != NULL);
	assert(list != NULL);

	iterator->Index = 0;
	iterator->List = list;
	iterator->Position = list->First;
}

void LinkedList_ResetIterator(LinkedList_Iterator* iterator) {
	assert(iterator != NULL);

	iterator->Position = iterator->List->First;
	iterator->Index = 0;
}

void LinkedList_Clear(LinkedList* self) {
	Node* prior;

	assert(self != NULL);

	while (self->First != NULL) {
		if (self->Disposer)
			self->Disposer(self->First->Data);

		prior = self->First;
		self->First = self->First->Next;
		Free(prior);
	}

	self->First = NULL;
	self->Last = NULL;
	self->Count = 0;
	LinkedList_ResetIterator(self->DefaultIterator);
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
	}
	else if (self->First == node) {
		self->First = node->Next;
		self->First->Prev = NULL;
	}
	else if (self->Last == node) {
		self->Last = node->Prev;
		self->Last->Next = NULL;
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
	}

	self->Count++;
}

void LinkedList_Insert(LinkedList_Iterator* iterator, void* data) {
	Node* node;

	assert(iterator != NULL && data != NULL);

	if (iterator->Position == NULL) {
		LinkedList_Append(iterator->List, data);
	}
	else {
		node = Allocate(Node);
		node->Data = data;

		node->Prev = iterator->Position;
		node->Next = iterator->Position->Next;
		iterator->Position->Next->Prev = node;
		iterator->Position->Next = node;
	}

	iterator->List->Count++;
}
