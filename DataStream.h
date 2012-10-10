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

public DataStream* DataStream_New(uint64 allocation);
public void DataStream_Initialize(DataStream* dataStream, uint64 allocation);
public void DataStream_Dispose(DataStream* self);

public void DataStream_Seek(DataStream* self, uint64 position);

public void DataStream_WriteInt8(DataStream* self, int8 data);
public void DataStream_WriteInt16(DataStream* self, int16 data);
public void DataStream_WriteInt32(DataStream* self, int32 data);
public void DataStream_WriteInt64(DataStream* self, int64 data);
public void DataStream_WriteUInt8(DataStream* self, uint8 data);
public void DataStream_WriteUInt16(DataStream* self, uint16 data);
public void DataStream_WriteUInt32(DataStream* self, uint32 data);
public void DataStream_WriteUInt64(DataStream* self, uint64 data);
public void DataStream_WriteFloat32(DataStream* self, float32 data);
public void DataStream_WriteFloat64(DataStream* self, float64 data);
public void DataStream_WriteBytes(DataStream* self, uint8* data, uint64 count, boolean disposeBytes);
public void DataStream_WriteArray(DataStream* self, Array* array, boolean disposeArray);
public void DataStream_WriteString(DataStream* self, String* string, boolean disposeString);

public int8 DataStream_ReadInt8(DataStream* self);
public int16 DataStream_ReadInt16(DataStream* self);
public int32 DataStream_ReadInt32(DataStream* self);
public int64 DataStream_ReadInt64(DataStream* self);
public uint8 DataStream_ReadUInt8(DataStream* self);
public uint16 DataStream_ReadUInt16(DataStream* self);
public uint32 DataStream_ReadUInt32(DataStream* self);
public uint64 DataStream_ReadUInt64(DataStream* self);
public float32 DataStream_ReadFloat32(DataStream* self);
public float64 DataStream_ReadFloat64(DataStream* self);
public uint8* DataStream_ReadBytes(DataStream* self, uint64 count);
public Array* DataStream_ReadArray(DataStream* self, uint64 count);
public String* DataStream_ReadString(DataStream* self);

#endif
