#ifndef INCLUDE_UTILITIES_STRING
#define INCLUDE_UTILITIES_STRING

#include "Common.h"
#include "Array.h"

typedef struct {
	Array Data;
	uint16 Length;
} String;


export String* String_New(uint16 size);
export String* String_NewFromCString(int8* cString);
export void String_Initialize(String* string, uint16 size);
export void String_Free(String* self);
export void String_Uninitialize(String* self);

export void String_AppendCString(String* self, int8* cString);
export void String_AppendBytes(String* self, int8* bytes, uint16 size);
export void String_AppendString(String* self, String* source);

export boolean String_IsUTF8(String* self);

#endif
