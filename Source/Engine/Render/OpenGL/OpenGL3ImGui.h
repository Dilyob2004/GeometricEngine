#ifndef OPENGL3IMGUI_H
#define OPENGL3IMGUI_H

#include <glew/glew.h> 

#include <ImGui/imgui.h>
#if !defined(IMGUI_IMPL_OPENGL_ES2) \
 && !defined(IMGUI_IMPL_OPENGL_ES3) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLEW) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

// Try to detect GLES on matching platforms
#if defined(__APPLE__)
#include "TargetConditionals.h"
#endif
#if (defined(__APPLE__) && (TARGET_OS_IOS || TARGET_OS_TV)) || (defined(__ANDROID__))
#define IMGUI_IMPL_OPENGL_ES3               // iOS, Android  -> GL ES 3, "#version 300 es"
#elif defined(__EMSCRIPTEN__)
#define IMGUI_IMPL_OPENGL_ES2               // Emscripten    -> GL ES 2, "#version 100"

// Otherwise try to detect supported Desktop OpenGL loaders..
#elif defined(__has_include)
#if __has_include(<glew/glew.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#elif __has_include(<glad/glad.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#elif __has_include(<glad/gl.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#elif __has_include(<GL/gl3w.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GL3W
#elif __has_include(<glbinding/glbinding.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLBINDING3
#elif __has_include(<glbinding/Binding.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLBINDING2
#else
#error "Cannot detect OpenGL loader!"
#endif
#else
#define IMGUI_IMPL_OPENGL_LOADER_GL3W   // Default to GL3W embedded in our repository
#endif

#endif
namespace MeteorEngine
{
    class OpenGL3ImGui
    {
    public:
        static bool Init(const char* glsl_version);
        static void Shutdown();
        static void NewFrame();
        static void RenderDrawData(ImDrawData* draw_data);

        static bool CreateFontsTexture();
        static void DestroyFontsTexture();
        static bool CreateDeviceObjects();
        static void DestroyDeviceObjects();

        struct Data
        {
            GLuint          GlVersion;               // Extracted at runtime using GL_MAJOR_VERSION, GL_MINOR_VERSION queries (e.g. 320 for GL 3.2)
            char            GlslVersionString[32];   // Specified by user or detected based on compile time GL settings.
            GLuint          FontTexture;
            GLuint          ShaderHandle;
            GLint           AttribLocationTex;       // Uniforms location
            GLint           AttribLocationProjMtx;
            GLuint          AttribLocationVtxPos;    // Vertex attributes location
            GLuint          AttribLocationVtxUV;
            GLuint          AttribLocationVtxColor;
            unsigned int    VboHandle, ElementsHandle;
            GLsizeiptr      VertexBufferSize;
            GLsizeiptr      IndexBufferSize;
            bool            HasClipOrigin;
            bool            UseBufferSubData;
            Data() { memset((void*)this, 0, sizeof(*this)); }
        };
        struct ViewportData
        {
            ViewportData()  {}
            ~ViewportData() {}
        };
        static Data* GetBackendData();
        static bool CheckShader(GLuint handle, const char* desc);
        static bool CheckProgram(GLuint handle, const char* desc);
        static void InitPlatformInterface();
        static void ShutdownPlatformInterface();
        static void SetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, GLuint vertex_array_object);
        static void RenderWindow(ImGuiViewport* viewport, void*);
    };

}
#endif // OPENGL3IMGUI_H
