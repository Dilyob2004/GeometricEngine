#ifndef FILEBASE_H
#define FILEBASE_H
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
	enum class FileAccess
	{
		Read,
		Write,
	};
	enum class FileShare
	{
		Read,
		Write,
		Delete,
		None,
	};
}
#endif // !FILEBASE_H
