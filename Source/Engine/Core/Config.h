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
enum class ShaderType
{
    FragmentShader,
    VertexShader,
    NoneShader
};
enum class ShaderDataType
{
    None = 0,
    Float,  Float2, Float3, Float4,
    Mat,    Mat2,   Mat3,   Mat4,
    Int,    Int2,   Int3,   Int4,
    Bool
};
#endif // CONFIG_H
