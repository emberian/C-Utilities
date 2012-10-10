#ifndef INCLUDE_UTILITIES_QUEUE
#define INCLUDE_UTILITIES_QUEUE

#include "Common.h"
#include "LinkedList.h"

typedef struct {
	LinkedList Data;
} Queue;

public Queue* Queue_New(void);
public void Queue_Initialize(Queue* queue);
public void Queue_Dispose(Queue* self);

public void* Queue_Dequeue(Queue* self);
public void Queue_Enqueue(Queue* self, void* toEnqueue);

#endif
