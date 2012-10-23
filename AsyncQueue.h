#ifndef INCLUDE_UTILITIES_ASYNCQUEUE
#define INCLUDE_UTILITIES_ASYNCQUEUE

#include "Common.h"
#include "Queue.h"
#include <SAL/Thread.h>

typedef struct {
	SAL_Mutex Lock;
	Queue* BaseQueue;
} AsyncQueue;

public AsyncQueue* AsyncQueue_New(void);
public void AsyncQueue_Initialize(AsyncQueue* queue);
public void AsyncQueue_Free(AsyncQueue* self);
public void AsyncQueue_Uninitialize(AsyncQueue* self);

public void* AsyncQueue_Dequeue(AsyncQueue* self);
public void AsyncQueue_Enqueue(AsyncQueue* self, void* toEnqueue);

#endif
