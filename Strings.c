#include "Strings.h"

#include <string.h>

String* String_New(uint16 size) {
	String* string;

	string = Allocate(String);
	String_Initialize(string, size);

	return string;
}

String* String_NewFromCString(int8* cString) {
	String* string;
	uint16 size;

	size = (uint16)strlen(cString);

	string = Allocate(String);
	String_Initialize(string, size);

	string->Length = 0;
	String_AppendCString(string, cString);

	return string;
}

void String_Initialize(String* string, uint16 size) {
	string->Length = size;
	Array_Initialize(&string->Data, size);
}

void String_Free(String* self) {
	String_Uninitialize(self);
	Free(self);
}

void String_Uninitialize(String* self) {
	assert(self != NULL);

	Array_Free(&self->Data);
	self->Length = 0;
}

void String_AppendCString(String* self, int8* cString) {
	uint16 size;

	assert(self != NULL);
	assert(cString != NULL);

	size = (uint16)strlen(cString);

	Array_Write(&self->Data, (uint8*)cString, self->Length, size);
	self->Length += size;
}

void String_AppendBytes(String* self, int8* bytes, uint16 size) {
	assert(self != NULL);
	assert(bytes != NULL);

	Array_Write(&self->Data, (uint8*)bytes, self->Length, size);
	self->Length += size;
}

void String_AppendString(String* self, String* source) {
	assert(self != NULL && source != NULL);

	Array_Append(&self->Data, &source->Data);
	self->Length += source->Length;
}

boolean String_IsUTF8(String* self) {
	uint16 length = self->Length;
	uint8 byte = 0;
	uint8 bytesToFind = 0;
	uint8 i;
	uint8* bytes;

	bytes = Array_Read(&self->Data, 0, self->Length);

	for (byte = bytes[i = 0]; i < length; byte = bytes[++i])
		if (bytesToFind == 0)
			if ((byte >> 1) == 126)
				bytesToFind = 5;
			else if ((byte >> 2) == 62)
				bytesToFind = 4;
			else if ((byte >> 3) == 30)
				bytesToFind = 3;
			else if ((byte >> 4) == 14)
				bytesToFind = 2;
			else if ((byte >> 5) == 6)
				bytesToFind = 1;
			else if ((byte >> 7) == 0) 
				;
			else
				return false;
		else
			if ((byte >> 6) == 2)
				bytesToFind--;
			else
				return false;

	return true;
}
