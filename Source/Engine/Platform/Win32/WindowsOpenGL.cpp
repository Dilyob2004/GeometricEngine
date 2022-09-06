#include <Engine/Platform/Win32/WindowsOpenGL.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>
namespace MeteorEngine
{


    WindowsOpenGL::WindowsOpenGL(HWND window)
    {
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = DefWindowProcA;
		wc.hInstance = GetModuleHandle(0);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		wc.lpszClassName = "DummyOpenGL";
		wc.hIcon = 0;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.lpszMenuName = 0;
		wc.hIconSm = 0;

		RegisterClassEx(&wc);

		HWND dummyWindow = CreateWindowA("DummyOpenGL", "DummyOpenGL", 0,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, NULL, GetModuleHandle(0), 0);


		HDC dummyDC = GetDC(dummyWindow);

        PIXELFORMATDESCRIPTOR pfd;
        pfd.nSize		 = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion	 = 1;
        pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType	 = PFD_TYPE_RGBA;
        pfd.cColorBits	 = 32;
        pfd.cDepthBits	 = 0;
        pfd.cStencilBits = 0;
        pfd.iLayerType	 = PFD_MAIN_PLANE;

		s32 pixelFormatStd = ChoosePixelFormat(dummyDC, &pfd);

		if (!pixelFormatStd)
			LOG("Failed to choose pixel format for device context.\n");


		if (!SetPixelFormat(dummyDC, pixelFormatStd, &pfd))
			LOG("Failed to set pixel format for device context.\n");

        HGLRC dummyRC = wglCreateContext(dummyDC);
		if (!dummyRC)
			LOG("Failed to create context.\n");

		if (!wglMakeCurrent(dummyDC, dummyRC))
			LOG("Failed to make current context\n");




		InitPlatformGL();

		wglMakeCurrent(dummyDC, 0);
		wglDeleteContext(dummyRC);
		ReleaseDC(dummyWindow, dummyDC);
		DestroyWindow(dummyWindow);

		m_wnd = window;
		m_hdc = GetDC(m_wnd);
		s32 attrList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, true,
			WGL_SUPPORT_OPENGL_ARB, true,
			WGL_ACCELERATION_ARB,
			WGL_FULL_ACCELERATION_ARB,
			WGL_DOUBLE_BUFFER_ARB, true,
			WGL_COLOR_BITS_ARB, 32,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, true,
			WGL_SAMPLE_BUFFERS_ARB, true,
			WGL_SAMPLES_ARB, 2 , 0, 0
		};
		s32 pixelFormat;
		u32 numFormats;

		if (!wglChoosePixelFormatARB(m_hdc, attrList, NULL, 1, &pixelFormat, &numFormats))
			LOG("Failed to choose pixel format for device context ARB.\n");


		PIXELFORMATDESCRIPTOR pfdARB;
		DescribePixelFormat(m_hdc, pixelFormat, sizeof(pfdARB), &pfdARB);
		if (!SetPixelFormat(m_hdc, pixelFormat, &pfdARB))
			LOG("Failed to set pixel format for device context ARB.\n");
		int AttribList[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB,
			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		m_hrc = wglCreateContextAttribsARB(m_hdc, NULL, AttribList);
		if (!m_hrc)
			LOG("Failed to create context ARB.\n");
		MakeCurrent(true);
		
        s32 glVersion[2] = {-1, -1};
        glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
        glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
        std::clog << "GPU API: OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;
    }
    WindowsOpenGL::~WindowsOpenGL()
    {
        MakeCurrent(false);
        wglDeleteContext(m_hrc);
        ReleaseDC(m_wnd, m_hdc);

    }
    void* WindowsOpenGL::GetCurrent()
    {
        return reinterpret_cast<void*>(wglGetCurrentContext());
    }

    void WindowsOpenGL::MakeCurrent(bool enabled)
    {
		if (!wglMakeCurrent(m_hdc, enabled ? m_hrc : NULL))
			LOG("Failed to make current context ARB\n");
    }
    void WindowsOpenGL::SetVSync(bool enabled)
    {
		if(wglSwapIntervalEXT)
			wglSwapIntervalEXT(enabled ? 1 : 0);
		else
			LOG("Failed to load function: wglSwapIntervalEXT.\n");

    }
    void WindowsOpenGL::Renderer()
    {
		if (!SwapBuffers(m_hdc))
			LOG("Failed to swap buffers\n");
    }

}
