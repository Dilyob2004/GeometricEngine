#ifndef  PATH_H
#define PATH_H
#include <Engine/Core/Misc/String.h>
namespace GeometricEngine
{
	class SPath
	{
	public:
		static String GetEngineDir()
		{
			return "../../Source/Engine/";
		}
		static String GetEngineEditorDir()
		{
			return "../../Source/Editor/";
		}
		static String GetEngineShaderDir()
		{
			return "../../Source/Shaders/";
		}
		static String GetEngineContentDir()
		{
			return "../../Content/";
		}
	};
}
#endif // ! PATH_H
