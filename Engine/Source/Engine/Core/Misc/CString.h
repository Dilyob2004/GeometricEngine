#ifndef CSTRING_H
#define CSTRING_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{

	enum class ESearchCase
	{
		Sensitive,
		InSensitive,
	};
	class GEOMETRIC_API CString
	{
	public:
		static bool IsDigit(char);
		static bool IsLower(char);
		static bool IsUpper(char);
		static char ToLower(char);
		static char ToUpper(char);
		
		static I32		Length(const WCHAR*);
		static I32		Length(const CHAR*);
		static WCHAR*	Copy(WCHAR*, const WCHAR*);
		static CHAR*	Copy(CHAR*, const CHAR*);



		static I32 Compare(const CHAR*, const CHAR*);
		static I32 Compare(const CHAR*, const CHAR*, I32);
		static I32 CompareCaseInSensitive(const CHAR*, const CHAR*);
		static I32 CompareCaseInSensitive(const CHAR*, const CHAR*, I32);


		static I32 Compare(const WCHAR*, const WCHAR*);
		static I32 Compare(const WCHAR*, const WCHAR*, I32);
		static I32 CompareCaseInSensitive(const WCHAR*, const WCHAR*);
		static I32 CompareCaseInSensitive(const WCHAR*, const WCHAR*, I32);


		static const CHAR* Find(const CHAR*, const CHAR*);
		static const WCHAR* Find(const WCHAR*, const WCHAR*);



		static const CHAR* FindCaseInSensitive(const CHAR*, const CHAR*);
		static const WCHAR* FindCaseInSensitive(const WCHAR*, const WCHAR*);
	};
}

#endif // !CSTRING_H
