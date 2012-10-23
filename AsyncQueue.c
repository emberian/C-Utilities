#include "AsyncQueue.h"

AsyncQueue* AsyncQueue_New(void) {
	AsyncQueue* queue;

	queue = Allocate(AsyncQueue);
	AsyncQueue_Initialize(queue);

	return queue;
}

void AsyncQueue_Initialize(AsyncQueue* queue) {
	assert(queue != NULL);

	queue->BaseQueue = Queue_New();
	queue->Lock = SAL_Mutex_Create();
}

void AsyncQueue_Free(AsyncQueue* self) {
	assert(self != NULL);
	AsyncQueue_Uninitialize(self);
	Free(self);
}

void AsyncQueue_Uninitialize(AsyncQueue* self) {
	assert(self != NULL);

	Queue_Free(self->BaseQueue);
	SAL_Mutex_Free(self->Lock);
}

void* AsyncQueue_Dequeue(AsyncQueue* self) {
	void* data;
	
	assert(self != NULL);

	SAL_Mutex_Acquire(self->Lock);
	data = Queue_Dequeue(self->BaseQueue);
	SAL_Mutex_Release(self->Lock);

	return data;
}

void AsyncQueue_Enqueue(AsyncQueue* self, void* toEnqueue) {
	assert(self != NULL);
	SAL_Mutex_Acquire(self->Lock);
	Queue_Dequeue(self->BaseQueue);
	SAL_Mutex_Release(self->Lock);
}
