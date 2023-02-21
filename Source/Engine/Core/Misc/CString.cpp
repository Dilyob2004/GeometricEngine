

#define _CRT_SECURE_NO_WARNINGS
#include <Engine/Core/Config.h>
#include <Engine/Core/Misc/CString.h>
namespace GeometricEngine
{
	bool CString::IsDigit(char c)
	{
		return isdigit(c);
	}
	bool CString::IsLower(char c)
	{
		return islower(c);
	}
	bool CString::IsUpper(char c)
	{
		return isupper(c);
	}
	char CString::ToLower(char c)
	{
		return tolower(c);
	}
	char CString::ToUpper(char c)
	{
		return toupper(c);
	}
	I32 CString::Length(const WCHAR* Source)
	{
		return static_cast<I32>(wcslen(Source));
	}
	I32		CString::Length(const CHAR* Source)
	{
		return static_cast<I32>(strlen(Source));
	}
	WCHAR* CString::Copy(WCHAR* Destination, const WCHAR* Source)
	{
		return static_cast <WCHAR*>(wcscpy(Destination, Source));
	}
	CHAR* CString::Copy(CHAR* Destination, const CHAR* Source)
	{
		return static_cast <CHAR*>(strcpy(Destination, Source));
	}



	I32 CString::Compare(const CHAR* Source1, const CHAR* Source2)
	{
		return strcmp(Source1, Source2);
	}
	I32 CString::Compare(const CHAR* Source1, const CHAR* Source2, I32 Count)
	{
		return strncmp(Source1, Source2, Count);
	}
	I32 CString::CompareCaseInSensitive(const CHAR* Source1, const CHAR* Source2)
	{
		return _strcmpi(Source1, Source2);
	}
	I32 CString::CompareCaseInSensitive(const CHAR* Source1, const CHAR* Source2, I32 Count) 
	{
		return _strnicmp(Source1, Source2, Count);
	}

	I32 CString::Compare(const WCHAR* Source1, const WCHAR* Source2)
	{
		return wcscmp(Source1, Source2);
	}
	I32 CString::Compare(const WCHAR* Source1, const WCHAR* Source2, I32 Count)
	{
		return wcsncmp(Source1, Source2, Count);
	}
	I32 CString::CompareCaseInSensitive(const WCHAR* Source1, const WCHAR* Source2)
	{
		return _wcsicmp(Source1, Source2);
	}
	I32 CString::CompareCaseInSensitive(const WCHAR* Source1, const WCHAR* Source2, I32 Count)
	{
		return _wcsnicmp(Source1, Source2, Count);
	}
	

	const CHAR* CString::Find(const CHAR* Source1, const CHAR* SubStr)
	{
		return strstr(Source1, SubStr);
	}
	const WCHAR* CString::Find(const WCHAR* Source1, const WCHAR* Source2)
	{
		return wcsstr(Source1, Source2);
	}


	
	const CHAR* CString::FindCaseInSensitive(const CHAR*, const CHAR*)
	{
		return "";

	}
	const WCHAR* CString::FindCaseInSensitive(const WCHAR*, const WCHAR*)
	{
		return L"";

	}
}
#undef _CRT_SECURE_NO_WARNINGS