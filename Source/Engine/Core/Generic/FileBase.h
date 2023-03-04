#ifndef FILEBASE_H
#define FILEBASE_H

#include <Engine/Core/Config.h>


namespace GeometricEngine
{
	enum class FileMode
	{
		CreateNew			= 1,
		CreateAlways		= 2,
		OpenExisting		= 3,
		OpenAlways			= 4,
		TruncateExisting	= 5
	};
	enum class FileAccess : long long
	{
		Read = 0x80000000,
		Write = 0x40000000,
		ReadWrite = Read | Write,
	};
	enum class FileShare
	{
		Read = 0x00000001,
		Write = 0x00000002,
		Delete = 0x00000004,
		None = 0x00000000,
		ReadWrite = Read | Write,
		All = ReadWrite | Delete

	};
}
#endif // !FILEBASE_H
