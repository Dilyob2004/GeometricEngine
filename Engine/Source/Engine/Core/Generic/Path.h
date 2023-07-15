#ifndef  PATH_H
#define PATH_H
#include <Engine/Core/Misc/String.h>
class SPath
{
public:
	static String GetEngineDir()
	{
		return ("../../Source/Engine");
	}
	static String GetEngineEditorDir()
	{
		return ("../../Source/Editor");
	}
	static String GetEngineShadersDir()
	{
		return ("../../Source/Shaders");
	}
	static String GetEngineContentDir()
	{
		return ("../../Content");
	}
};

struct FPathInfo
{
	FPathInfo() = default;
	String Name = "";
	bool IsDirectory = false;
};
#endif // ! PATH_H
