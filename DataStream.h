#ifndef INCLUDE_UTILITIES_DATASTREAM
#define INCLUDE_UTILITIES_DATASTREAM

#include "Common.h"
#include "Array.h"
#include "Strings.h"

typedef struct {
	Array Data;
	uint64 Cursor;
	boolean IsEOF;
} DataStream;

export DataStream* DataStream_New(uint64 allocation);
export void DataStream_Initialize(DataStream* dataStream, uint64 allocation);
export void DataStream_Free(DataStream* self);
export void DataStream_Uninitialize(DataStream* self);

export void DataStream_Seek(DataStream* self, uint64 position);

export void DataStream_WriteInt8(DataStream* self, int8 data);
export void DataStream_WriteInt16(DataStream* self, int16 data);
export void DataStream_WriteInt32(DataStream* self, int32 data);
export void DataStream_WriteInt64(DataStream* self, int64 data);
export void DataStream_WriteUInt8(DataStream* self, uint8 data);
export void DataStream_WriteUInt16(DataStream* self, uint16 data);
export void DataStream_WriteUInt32(DataStream* self, uint32 data);
export void DataStream_WriteUInt64(DataStream* self, uint64 data);
export void DataStream_WriteFloat32(DataStream* self, float32 data);
export void DataStream_WriteFloat64(DataStream* self, float64 data);
export void DataStream_WriteBytes(DataStream* self, uint8* data, uint64 count, boolean disposeBytes);
export void DataStream_WriteArray(DataStream* self, Array* array, boolean disposeArray);
export void DataStream_WriteString(DataStream* self, String* string, boolean disposeString);

export int8 DataStream_ReadInt8(DataStream* self);
export int16 DataStream_ReadInt16(DataStream* self);
export int32 DataStream_ReadInt32(DataStream* self);
export int64 DataStream_ReadInt64(DataStream* self);
export uint8 DataStream_ReadUInt8(DataStream* self);
export uint16 DataStream_ReadUInt16(DataStream* self);
export uint32 DataStream_ReadUInt32(DataStream* self);
export uint64 DataStream_ReadUInt64(DataStream* self);
export float32 DataStream_ReadFloat32(DataStream* self);
export float64 DataStream_ReadFloat64(DataStream* self);
export uint8* DataStream_ReadBytes(DataStream* self, uint64 count);
export Array* DataStream_ReadArray(DataStream* self, uint64 count);
export String* DataStream_ReadString(DataStream* self);

#endif
