#include "HashTable.h"

#include "LinkedList.h"

#define BUCKET_COUNT 503

typedef struct Entry Entry;
typedef struct Bucket Bucket;

struct Entry {
	uint8* Key;
	uint8* Value;
	uint32 KeyLength;
	uint32 ValueLength;
};

struct Bucket {
	LinkedList Entries;
};

struct HashTable {
	Bucket Buckets[BUCKET_COUNT];
};

static Entry* GetEntryInBucket(Bucket* bucket, uint8* key, uint32 keyLength);
static uint64 ComputeHash(uint8* key, uint32 keyLength);

HashTable* HashTable_New() {
	HashTable* table;
	
	table = Allocate(HashTable);
	HashTable_Initialize(table);

	return table;
}

void HashTable_Initialize(HashTable* table) {
	uint16 i;

	assert(table != NULL);

	for (i = 0; i < BUCKET_COUNT; i++)
		LinkedList_Initialize(&table->Buckets[i].Entries, Memory_Free);
}

void HashTable_Free(HashTable* self) {
	HashTable_Uninitialize(self);

	Free(self);
}

void HashTable_Uninitialize(HashTable* self) {
	uint32 i;
	Bucket* bucket;
	Entry* entry;

	assert(self != NULL);

	bucket = self->Buckets;
	i = 0;

	while (i < BUCKET_COUNT) {
		LinkedList_ForEach(entry, &bucket->Entries, Entry*) {
			Free(entry->Key);
			Free(entry->Value);
		}

		LinkedList_Uninitialize(&bucket->Entries);
		bucket++;
		i++;
	}
}

void* HashTable_Get(HashTable* self, uint8* key, uint32 keyLength, void** value, uint32* valueLength) {
	uint32 index;
	Bucket* bucket;
	Entry* entry;
	
	assert(self != NULL);

	if (key == NULL)
		return NULL;
		
	index = ComputeHash(key, keyLength) % BUCKET_COUNT;
	bucket = self->Buckets + index;
	entry = GetEntryInBucket(bucket, key, keyLength);

	if (entry == NULL) {
		if (valueLength)
			*valueLength = 0;

		if (*value)
			*value = NULL;

		return NULL;
	}
	else {
		if (valueLength)
			*valueLength = entry->ValueLength;

		if (*value)
			*value = entry->Value;

		return entry->Value;
	}
}

void HashTable_Add(HashTable* self, uint8* key, uint32 keyLength, void* value, uint32 valueLength) {
	uint32 index;
	Bucket* bucket;
	Entry* entry;

	assert(self != NULL);

	if (key == NULL || value == NULL)
		return;
	
	index = ComputeHash(key, keyLength) % BUCKET_COUNT;
	bucket = self->Buckets + index;
	entry = GetEntryInBucket(bucket, key, keyLength);

	if (entry) {
		if (entry->ValueLength < valueLength) 
			entry->Value = ReallocateArray(uint8, valueLength, entry->Value);

		Memory_BlockCopy((uint8*)value, entry->Value, valueLength);
	}
	else {
		entry = Allocate(Entry);
		entry->Key = AllocateArray(uint8, keyLength);
		entry->Value = AllocateArray(uint8, valueLength);
		
		Memory_BlockCopy(key, entry->Key, keyLength);
		Memory_BlockCopy((uint8*)value, entry->Value, valueLength);

		LinkedList_Append(&bucket->Entries, entry);
	}
}

void HashTable_Remove(HashTable* self, uint8* key, uint32 keyLength) {
	uint32 index;
	Bucket* bucket;
	Entry* entry;
	
	assert(self != NULL);

	if (key == NULL)
		return;
		
	index = ComputeHash(key, keyLength) % BUCKET_COUNT;
	bucket = self->Buckets + index;
	entry = GetEntryInBucket(bucket, key, keyLength);

	if (entry) {
		Free(entry->Key);
		Free(entry->Value);
		LinkedList_Remove(&bucket->Entries, entry);
	}
}

void* HashTable_GetInt(HashTable* self, uint64 key, void** value, uint32* valueLength) {
	return HashTable_Get(self, (uint8*)&key, sizeof(key), value, valueLength);
}

void HashTable_AddInt(HashTable* self, uint64 key, void* value, uint32 valueLength) {
	HashTable_Add(self, (uint8*)&key, sizeof(key), value, valueLength);
}

void HashTable_RemoveInt(HashTable* self, uint64 key) {
	HashTable_Remove(self, (uint8*)&key, sizeof(key));
}



static Entry* GetEntryInBucket(Bucket* bucket, uint8* key, uint32 keyLength) {
	Entry* entry;

	LinkedList_ForEach(entry, &bucket->Entries, Entry*)
		if ( Memory_Compare(entry->Key, key, entry->KeyLength, keyLength) )
			return entry;

	return NULL;
}

static uint64 ComputeHash(uint8* key, uint32 keyLength) {
	uint64 hash = 5046436453;
	
	while (--keyLength)
		hash = ((hash << 7) + hash) + key[keyLength];

	return hash;
}
