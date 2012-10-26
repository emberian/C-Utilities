#include "DataStream.h"

DataStream* DataStream_New(uint64 allocation) {
	DataStream* dataStream;

	dataStream = Allocate(DataStream);
	DataStream_Initialize(dataStream, allocation);

	return dataStream;
}

void DataStream_Initialize(DataStream* dataStream, uint64 allocation) {
	uint64 actualSize;

	assert(dataStream != NULL);

	actualSize = 32;
	while (actualSize < allocation)
		actualSize *= 2;

	dataStream->Cursor = 0;
	dataStream->IsEOF = false;
	Array_Initialize(&dataStream->Data, actualSize);
}

void DataStream_Free(DataStream* self) {
	DataStream_Uninitialize(self);
	Free(self);
}

void DataStream_Uninitialize(DataStream* self) {
	assert(self != NULL);

	Array_Uninitialize(&self->Data);
	self->Cursor = 0;
	self->IsEOF = true;
}

void DataStream_Seek(DataStream* self, uint64 position) {
	assert(self != NULL);

	if (position >= self->Data.Size)
		self->Cursor = self->Data.Size - 1;
	else
		self->Cursor = position;

	self->IsEOF = false;
}

void DataStream_WriteUInt8(DataStream* self, uint8 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteUInt16(DataStream* self, uint16 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteUInt32(DataStream* self, uint32 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteUInt64(DataStream* self, uint64 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteInt8(DataStream* self, int8 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteInt16(DataStream* self, int16 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteInt32(DataStream* self, int32 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteInt64(DataStream* self, int64 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteFloat32(DataStream* self, float32 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteFloat64(DataStream* self, float64 data) {
	DataStream_WriteBytes(self, (uint8*)&data, sizeof(data), false);
}

void DataStream_WriteBytes(DataStream* self, uint8* data, uint64 count, boolean disposeBytes) {
	assert(self != NULL);
	assert(data != NULL);

	Array_Write(&self->Data, data, self->Cursor, count);
	self->Cursor += count;

	if (disposeBytes)
		Free(data);
}

void DataStream_WriteArray(DataStream* self, Array* array, boolean disposeArray) {
	assert(self != NULL);
	assert(array != NULL);

	Array_Append(&self->Data, array);

	if (disposeArray)
		Array_Free(array);
}

void DataStream_WriteString(DataStream* self, String* string, boolean disposeString) {
	DataStream_WriteBytes(self, (uint8*)&string->Length, sizeof(string->Length), false);
	DataStream_WriteArray(self, &string->Data, false);

	if (disposeString)
		String_Free(string);
}

int8 DataStream_ReadInt8(DataStream* self) {
	int8 result = 0;

	if (self->Cursor + sizeof(int8) < self->Data.Size) {
		result = *(int8*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(int8);
	}
	else
		self->IsEOF = true;

	return result;
}

int16 DataStream_ReadInt16(DataStream* self) {
	int16 result = 0;

	if (self->Cursor + sizeof(int16) <= self->Data.Size) {
		result = *(int16*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(int16);
	}
	else
		self->IsEOF = true;

	return result;
}

int32 DataStream_ReadInt32(DataStream* self) {
	int32 result = 0;

	if (self->Cursor + sizeof(int32) <= self->Data.Size) {
		result = *(int32*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(int32);
	}
	else
		self->IsEOF = true;

	return result;
}

int64 DataStream_ReadInt64(DataStream* self) {
	int64 result = 0;

	if (self->Cursor + sizeof(int64) <= self->Data.Size) {
		result = *(long*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(int64);
	}
	else
		self->IsEOF = true;

	return result;
}

uint8 DataStream_ReadUInt8(DataStream* self) {
	uint8 result = 0;

	if (self->Cursor + sizeof(uint8) <= self->Data.Size) {
		result = *(uint8*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(uint8);
	}
	else
		self->IsEOF = true;

	return result;
}

uint16 DataStream_ReadUInt16(DataStream* self) {
	uint16 result = 0;

	if (self->Cursor + sizeof(uint16) <= self->Data.Size) {
		result = *(uint16*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(uint16);
	}
	else
		self->IsEOF = true;

	return result;
}

uint32 DataStream_ReadUInt32(DataStream* self) {
	uint32 result = 0;

	if (self->Cursor + sizeof(uint32) <= self->Data.Size) {
		result = *(uint32*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(uint32);
	}
	else
		self->IsEOF = true;

	return result;
}

uint64 DataStream_ReadUInt64(DataStream* self) {
	uint64 result = 0;

	if (self->Cursor + sizeof(uint64) <= self->Data.Size) {
		result = *(unsigned long*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(uint64);
	}
	else
		self->IsEOF = true;

	return result;
}

float32 DataStream_ReadFloat32(DataStream* self) {
	float32 result = 0;

	if (self->Cursor + sizeof(float32) <= self->Data.Size) {
		result = *(float32*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(float32);
	}
	else
		self->IsEOF = true;

	return result;
}

float64 DataStream_ReadFloat64(DataStream* self) {
	float64 result = 0;

	if (self->Cursor + sizeof(float64) <= self->Data.Size) {
		result = *(float64*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(float64);
	}
	else
		self->IsEOF = true;

	return result;
}

/*should this return a pointer within the backing data store itself or create a new allocation and return that?*/
uint8* DataStream_ReadBytes(DataStream* self, uint64 count) {
	uint8* result;

	result = NULL;

	if (self->Cursor + count < self->Data.Size) {
		result = self->Data.Data + self->Cursor + count - 1;
		self->Cursor += count;
	}
	else
		self->IsEOF = true;

	return result;
}

Array* DataStream_ReadArray(DataStream* self, uint64 count) {
	Array* array;

	array = NULL;

	if (self->Cursor + count <= self->Data.Size) {
		array = Array_New(count);
		Array_Write(array, self->Data.Data + self->Cursor, 0, count);
		self->Cursor += count;
	}
	else {
		self->IsEOF = true;
	}

	return array;
}

String* DataStream_ReadString(DataStream* self) {
	uint16 length;
	String* string;

	string = NULL;
	length = 0;

	if (self->Cursor + sizeof(uint16) <= self->Data.Size) {
		length = *(uint16*)(self->Data.Data + self->Cursor);
		self->Cursor += sizeof(uint16);

		if (self->Cursor + length <= self->Data.Size) {
			string = String_New(length);
			String_AppendBytes(string, (int8*)(self->Data.Data + self->Cursor), length);
			self->Cursor += length;
		}
		else {
			self->IsEOF = true;
			self->Cursor -= sizeof(uint16);
		}
	}
	else
		self->IsEOF = true;

	return string;
}
