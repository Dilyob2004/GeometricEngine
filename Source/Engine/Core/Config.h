#ifndef CONFIG_H
#define CONFIG_H
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> 

#if defined (METEOR_BUILD_DLL)

    #define METEOR_API __declspec(dllexport)
#else

    #define METEOR_API __declspec(dllimport)
#endif


#define LOG(x) std::clog << x
#define LOGLN(x) std::clog << x << "\n"
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_RADIANS				0.01745329251994329576923690768489f
#define MIN(a, b) (( (a) < (b) ) ? (a) : (b))
#define MAX(a, b) (( (a) > (b) ) ? (a) : (b))
typedef void	s0;
typedef void*	p0;

typedef signed char     s8;
typedef signed short    s16;
typedef signed int      s32;
typedef signed long     s64;

typedef unsigned char     u8;
typedef unsigned short    u16;
typedef unsigned int      u32;
typedef unsigned long     u64;


typedef float f32;
typedef double f64;



enum class RHIPixelFormat : u32
{
	NONE = 0,

	R8_UNORM,
	RG8_UNORM,
	RGB8_UNORM,
	RGBA8_UNORM,

	R8_U32,

	RG11B10_F32,
	RGB10A2_UNORM,

	R32_S32,
	RG32_S32,
	RGB32_S32,
	RGBA32_S32,

	R32_U32,
	RG32_U32,
	RGB32_U32,
	RGBA32_U32,

	R16_F32,
	RG16_F32,
	RGB16_F32,
	RGBA16_F32,

	R32_F32,
	RG32_F32,
	RGB32_F32,
	RGBA32_F32,

	DEPTH16_UNORM,
	DEPTH32_F32,

	DEPTH16_UNORM_STENCIL8_U32,
	DEPTH24_UNORM_STENCIL8_U32,
	DEPTH32_F32_STENCIL8_U32
};
enum class TextureWrap
{
	NONE,
	REPEAT,
	CLAMP,
	CLAMP_TO_EDGE
};
enum class TextureType
{
	COLOR = 0,
	DEPTH
};
enum class TextureFilter
{
	NONE,
	LINEAR,
	NEAREST
};
enum TextureFlags : u16
{
	Texture_Sampled = (0),
	Texture_Storage = (1),
	Texture_RenderTarget = (2),
	Texture_DepthStencil = (3),
	Texture_DepthStencilReadOnly = (4),
	Texture_CreateMips = (5),
	Texture_MipViews = (6)
};
enum class ShaderType
{
	FRAGMENT,
	VERTEX,
	NONE
};
enum class ShaderDataType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Mat, Mat2, Mat3, Mat4,
	Int, Int2, Int3, Int4,
	Bool
};
#endif // CONFIG_H
