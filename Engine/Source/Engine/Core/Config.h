#ifndef CONFIG_H
#define CONFIG_H
#if defined (BUILD_DLL)
    #define GEOMETRIC_API __declspec(dllexport)
#else
    #define GEOMETRIC_API __declspec(dllimport)
#endif

#define MS_ALIGN(n) __declspec	(align(n))
#define FORCEINLINE	__forceinline
#define INLINE			__inline
#define RESTRICT		__restrict
#define CONSTEXPR		constexpr
#define ARRAY_COUNT(X) sizeof(X) / sizeof(typeid(X).raw_name())
#define DYNAMIC_CAST(Type, Name, Value) Type* Name = (Type*) Value
#define OVERRIDE override
#define FINAL final



#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma warning(disable: 4251)

typedef char     I8;
typedef short    I16;
typedef int      I32;
typedef long     I64;
typedef long long     I128;

typedef signed char         S8;
typedef signed short        S16;
typedef signed int          S32;
typedef signed long         S64;
typedef signed long long    S128;

typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned int        U32;
typedef unsigned long       U64;
typedef unsigned long long  U128;

typedef float	F32;
typedef double	F64;

typedef wchar_t	 Char;
typedef char	 CharAnsi;


struct FTimeItems
{
	int Years;
	int Month;
	int Week;
	int Day;
	int Hour;
	int Minute;
	int Second;
	int MilliSecond;
};

#endif // CONFIG_H