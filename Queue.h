#ifndef INCLUDE_UTILITIES_QUEUE
#define INCLUDE_UTILITIES_QUEUE

#include "Common.h"
#include "LinkedList.h"

typedef struct {
	LinkedList Data;
} Queue;

export Queue* Queue_New(void);
export void Queue_Initialize(Queue* queue);
export void Queue_Free(Queue* self);
export void Queue_Uninitialize(Queue* self);

export void* Queue_Dequeue(Queue* self);
export void Queue_Enqueue(Queue* self, void* toEnqueue);

#endif
