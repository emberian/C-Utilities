#ifndef INCLUDE_UTILITIES_ASYNCQUEUE
#define INCLUDE_UTILITIES_ASYNCQUEUE

#include "Common.h"
#include "Queue.h"
#include <SAL/Thread.h>

typedef struct {
	SAL_Mutex Lock;
	Queue* BaseQueue;
} AsyncQueue;

export AsyncQueue* AsyncQueue_New(void);
export void AsyncQueue_Initialize(AsyncQueue* queue);
export void AsyncQueue_Free(AsyncQueue* self);
export void AsyncQueue_Uninitialize(AsyncQueue* self);

export void* AsyncQueue_Dequeue(AsyncQueue* self);
export void AsyncQueue_Enqueue(AsyncQueue* self, void* toEnqueue);

#endif
