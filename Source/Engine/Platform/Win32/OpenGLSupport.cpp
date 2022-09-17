#include <Engine/Platform/Win32/OpenGLSupport.h>
#include <Engine/Platform/Platform.h>

#define DECLARE_GL_ENTRYPOINTS(Type,Func) Type Func = NULL;
ENUM_GL_ENTRYPOINTS_ALL(DECLARE_GL_ENTRYPOINTS);
#undef DECLARE_GL_ENTRYPOINTS


namespace MeteorEngine {
	void InitPlatformGL()
	{
		#define GET_GL_ENTRYPOINTS_DLL(Type,Func) Func = (Type)Platform::GetDllFunction("opengl32.dll", TEXT(#Func));
				ENUM_GL_ENTRYPOINTS_DLL(GET_GL_ENTRYPOINTS_DLL);
		#undef GET_GL_ENTRYPOINTS_DLL

		#define GET_WGL_ENTRYPOINTS_DLL(Type,Func) Func = (Type)wglGetProcAddress(TEXT(#Func));
				ENUM_WGL_ENTRYPOINTS(GET_WGL_ENTRYPOINTS_DLL);
		#undef GET_GL_ENTRYPOINTS_DLL



		#define GET_GL_ENTRYPOINTS(Type,Func) Func = (Type)wglGetProcAddress(TEXT(#Func));
				ENUM_GL_ENTRYPOINTS(GET_GL_ENTRYPOINTS);
				ENUM_GL_ENTRYPOINTS_OPTIONAL(GET_GL_ENTRYPOINTS);
		#undef GET_GL_ENTRYPOINTS

	}
}