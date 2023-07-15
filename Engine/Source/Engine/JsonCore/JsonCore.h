#pragma once
#include <ThirdParty/rapidjson/rapidjson.h>
#include <ThirdParty/rapidjson/writer.h>
#include <ThirdParty/rapidjson/prettywriter.h>
#include <ThirdParty/rapidjson/document.h>
#include <ThirdParty/rapidjson/stringbuffer.h>
#include <Engine/Core/Generic/Memory.h>

class EngineAllocator
{
public:
	static const bool kNeedFree = true;

	void* Malloc(U32 Size)
	{
		if (Size)
			return SMemory::Allocate(Size);
		return nullptr;
	}
	static void* Realloc(void* Ptr, U32 OldSize, U32 NewSize)
	{
		return SMemory::Realloc(Ptr, (U64)OldSize, (U64)NewSize);
	}

	static void Free(void* Ptr)
	{
		SMemory::Free(Ptr);
	}
}; 


typedef rapidjson::GenericStringBuffer<rapidjson::UTF8<>, EngineAllocator > StringBuffer;
typedef rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<EngineAllocator>, EngineAllocator> Document;
typedef rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<EngineAllocator>> Value;
//template<typename OutputStream, typename SourceEncoding = rapidjson::UTF8<>, typename TargetEncoding = rapidjson::UTF8<>, unsigned writeFlags = rapidjson::kWriteDefaultFlags>
//using Writer = rapidjson::Writer<OutputStream, SourceEncoding, TargetEncoding, EngineAllocator, writeFlags>;

template<typename OutputStream, typename SourceEncoding = rapidjson::UTF8<>, typename TargetEncoding = rapidjson::UTF8<>, unsigned writeFlags = rapidjson::kWriteDefaultFlags>
using Writer = rapidjson::PrettyWriter<OutputStream, SourceEncoding, TargetEncoding, EngineAllocator, writeFlags>;
