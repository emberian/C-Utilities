#ifndef INCLUDE_UTILITIES_STRING
#define INCLUDE_UTILITIES_STRING

#include "Common.h"
#include "Array.h"

typedef struct {
    Array Data;
	uint16 Length;
} String;


public String* String_New(uint16 size);
public String* String_NewFromCString(const char* cString);
public void String_Initialize(String* string, uint16 size);

public void String_Dispose(String* self);

public void String_AppendCString(String* self, const char* cString);
public void String_AppendBytes(String* self, const int8* bytes, uint16 size);
public void String_AppendString(String* self, String* source);

public boolean String_IsUTF8(String* self);

#endif
