#include "Memory.h"
#include <malloc.h>
#include <memory.h>

void* SMemory::Zero(void* Destination, U32 Size)
{
	return memset(Destination, 0, Size);
}
void SMemory::Free(void* Data)
{
	_aligned_free(Data);
}
void SMemory::Copy(void* Destination, const void* Source, U64 Size)
{
	memcpy(Destination, Source, static_cast<size_t>(Size));
}
void SMemory::Set(void* Destination, U32 Size, U32 Value)
{
	memset(Destination, Value, Size);
}
void SMemory::Clear(void* Destination, U32 Size)
{
	memset(Destination, 0, static_cast<size_t>(Size));
}
void* SMemory::Allocate(U32 Size, U32 Alignment)
{
	return _aligned_malloc(Size, Alignment);
}
void* SMemory::Realloc(void* Ptr, U64 OldSize, U64 NewSize)
{
	if (OldSize >= NewSize)
		return Ptr;
	void* Result = Allocate(NewSize);
	if (Result)
	{
		Copy(Result, Ptr, OldSize);
		Free(Ptr);
	}

	return Result;
}
void* SMemory::Realloc(void* Ptr, U64 Size)
{
	void* Result = Allocate(Size);
	if (Result)
	{
		Copy(Result, Ptr, Size);
		Free(Ptr);
	}

	return Result;
}
