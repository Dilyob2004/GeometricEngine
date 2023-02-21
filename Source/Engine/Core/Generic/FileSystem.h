#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Generic/Path.h>
#include <vector>
namespace GeometricEngine
{
	class METEOR_API FileSystem
	{
	public:

		static bool CreateDirectoryIn(const std::string&);
		static bool MoveFileTo(const std::string&, const std::string&, bool);
		static bool DeleteDirectory(const std::string&);
		static bool RemoveFile(const std::string&);
		static void Open(const Path& pathFile);
		static void Close();
		static std::vector<Path> FindDirectory(Path path);
	};

}
#endif // FILESYSTEM_H


