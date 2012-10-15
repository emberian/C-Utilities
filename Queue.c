#include "Queue.h"

Queue* Queue_New(void) {
	Queue* queue;

	queue = Allocate(Queue);
	Queue_Initialize(queue);

	return queue;
}

void Queue_Initialize(Queue* queue) {
	assert(queue != NULL);

	LinkedList_Initialize(&queue->Data, Memory_Free);
}

void Queue_Free(Queue* self) {
	Queue_Uninitialize(self);
	Free(self);
}

void Queue_Uninitialize(Queue* self) {
	assert(self != NULL);

	LinkedList_Free(&self->Data);
}

void* Queue_Dequeue(Queue* self) {
	void* data;

	assert(self != NULL);

	data = NULL;

	if (self->Data.Count != 0) {
		data = self->Data.Last->Data;
		LinkedList_RemoveNode(&self->Data, self->Data.Last);
	}

	return data;
}

void Queue_Enqueue(Queue* self, void* toEnqueue) {
	assert(self != NULL);

	LinkedList_Append(&self->Data, toEnqueue);
}
