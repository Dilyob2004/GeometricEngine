#ifndef WINDOWSFILESYSTEM_H
#define WINDOWSFILESYSTEM_H
#include <Engine/Core/Misc/StringView.h>
namespace GeometricEngine
{
	class GEOMETRIC_API WindowsFileSystem
	{
	public:
		static bool MakeDirectory(const StringView& Path);
		static bool DeleteDirectory(const StringView& Path);
		static bool DirectoryExists(const StringView& Path);

		static bool Move(const StringView&, const StringView&,  bool);
		static bool Copy(const StringView& To, const StringView& From);
		static bool Delete(const StringView& Path);
		static bool FileExists(const StringView& Path);
	};
}
#endif // !WINDOWSFILESYSTEM_H
