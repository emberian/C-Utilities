#include "Misc.h"

void Base64Encode(uint8* data, uint32 dataLength, int8** result, uint32* resultLength) {
	static char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static int32 mask = 0x3F;
	uint32 i, j, left;

	union {
		uint8 bytes[4];
		uint32 block;
	} buffer;

	*resultLength = dataLength + dataLength / 3 + (int32)(dataLength % 3 != 0);
	if (*resultLength % 4)
		*resultLength += 4 - *resultLength % 4;

	*result = AllocateArray(int8, *resultLength);

	for(i = 0, j = 0, left = dataLength; i < dataLength; i += 3, j += 4, left -= 3) {
		buffer.bytes[2] = data[i];
		if(left > 1) {
			buffer.bytes[1] = data[i + 1];
			if(left > 2)
				buffer.bytes[0] = data[i + 2];
			else
				buffer.bytes[0] = 0;
		}
		else {
			buffer.bytes[1] = 0;
			buffer.bytes[0] = 0;
		}

		(*result)[j] = characters[(buffer.block >> 18 ) & mask];
		(*result)[j + 1] = characters[(buffer.block >> 12 ) & mask];
		if(left > 1) {
			(*result)[ j + 2 ] = characters[(buffer.block >> 6) & mask];
			if( left > 2 )
				(*result)[j + 3] = characters[buffer.block & mask];
			else
				(*result)[j + 3] = '=';
		}
		else {
			(*result)[j + 2] = '=';
			(*result)[j + 3] = '=';
		}
	}
}
