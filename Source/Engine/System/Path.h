#ifndef  PATH_H
#define PATH_H
#include <string>
namespace MeteorEngine
{
	struct Path
	{
		Path() :
			m_path(""),
			fileName(""),
			isDirectory(false)
		{

		}
		Path(const std::string& path) :
			m_path(path),
			fileName(""),
			isDirectory(false)
		{
		}
		bool                isDirectory;
		std::string         fileName;
		std::string         m_path;
	};
}
#endif // ! PATH_H
