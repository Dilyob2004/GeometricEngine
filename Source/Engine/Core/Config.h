#ifndef CONFIG_H
#define CONFIG_H
#include <dwmapi.h>
#include <windows.h>
#include <iostream>


#if defined (GEOMETRIC_DEBUG)
    #define METEOR_API __declspec(dllexport)
    #define GEOMETRIC_API __declspec(dllexport)
#else
    #define METEOR_API __declspec(dllimport)
    #define GEOMETRIC_API __declspec(dllimport)
#endif

#define MS_ALIGN(n) __declspec	(align(n))
#define FORCEINLINE	__forceinline
#define INLINE			__inline
#define RESTRICT		__restrict
#define CONSTEXPR		constexpr
#define ARRAY_COUNT(X) sizeof(X) / sizeof(typeid(X).raw_name())
#define DYNAMIC_CAST(Type, Name, Value) Type* Name = (Type*) Value

#pragma warning(disable: 4251)

typedef char     I8;
typedef short    I16;
typedef int      I32;
typedef long     I64;

typedef signed char     S8;
typedef signed short    S16;
typedef signed int      S32;
typedef signed long     S64;

typedef unsigned char     U8;
typedef unsigned short    U16;
typedef unsigned int      U32;
typedef unsigned long     U64;

typedef float	F32;
typedef double	F64;

typedef wchar_t	 WCHAR;
typedef char	 CHAR;



#endif // CONFIG_H