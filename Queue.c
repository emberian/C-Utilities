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

void Queue_Dispose(Queue* self) {
    assert(self != NULL);

    LinkedList_Dispose(&self->Data);
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
