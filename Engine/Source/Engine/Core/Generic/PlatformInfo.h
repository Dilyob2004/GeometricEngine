#ifndef PLATFORMINFO_H
#define PLATFORMINFO_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{

	struct RAMStats
	{
		U128 TotalPhysical;
		U128 UsedPhysical;
		U128 TotalVirtual;
		U128 UsedVirtual;
	};
	struct CPUInfo
	{
		CHAR Name[0x40];
		U64 LogicalCount;
		U64 CoreCount;
		U64 L1CacheSize;
		U64 L2CacheSize;
		U64 L3CacheSize;
		U64 PackageCount;
	};
}
#endif // !PLATFORMINFO_H
