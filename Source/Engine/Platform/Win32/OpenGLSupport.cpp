#include <Engine/Platform/Win32/OpenGLSupport.h>


#include <Engine/Core/Config.h>
/** Declare all GL functions. */
#define DECLARE_GL_ENTRYPOINTS(Type,Func) Type Func = NULL;
ENUM_GL_ENTRYPOINTS_ALL(DECLARE_GL_ENTRYPOINTS);
#undef DECLARE_GL_ENTRYPOINTS

PFNWGLCREATECONTEXTATTRIBSARBPROC	wglCreateContextAttribsARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB = NULL;
PFNWGLSWAPINTERVALEXTPROC			wglSwapIntervalEXT = NULL;

void* getFunction(const char* name)
{
	void* address = NULL;
	address = reinterpret_cast<void*>(wglGetProcAddress(reinterpret_cast<LPCSTR>(name)));

	if (address)
	{
		ptrdiff_t errorCode = reinterpret_cast<ptrdiff_t>(address);

		if ((errorCode != -1) && (errorCode != 1) && (errorCode != 2) && (errorCode != 3))
			return address;
	}

	static HMODULE module = GetModuleHandleA("OpenGL32.dll");

	if (module) {
		address = reinterpret_cast<void*>(GetProcAddress(module, reinterpret_cast<LPCSTR>(name)));
		if (address)
			return address;
	}

	LOG("Failed Load Extensions: "); LOGLN(name);
	return 0;
}
void InitPlatformGL()
{

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	#define GET_GL_ENTRYPOINTS_DLL(Type,Func) Func = (Type)getFunction(TEXT(#Func));
		ENUM_GL_ENTRYPOINTS_DLL(GET_GL_ENTRYPOINTS_DLL);
	#undef GET_GL_ENTRYPOINTS_DLL


	#define GET_GL_ENTRYPOINTS(Type,Func) Func = (Type)getFunction(#Func);
		ENUM_GL_ENTRYPOINTS(GET_GL_ENTRYPOINTS);
		ENUM_GL_ENTRYPOINTS_OPTIONAL(GET_GL_ENTRYPOINTS);
	#undef GET_GL_ENTRYPOINTS

}