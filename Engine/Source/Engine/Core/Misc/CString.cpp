
#define _CRT_SECURE_NO_WARNINGS
#include "CString.h"
#include <Engine/Core/Config.h>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>

bool CString::IsDigit(Char c)
{
	return isdigit(c);
}
bool CString::IsLower(Char c)
{
	return islower(c);
}
bool CString::IsUpper(Char c)
{
	return isupper(c);
}
Char CString::ToLower(Char c)
{
	return tolower(c);
}
Char CString::ToUpper(Char c)
{
	return toupper(c);
}


I32 CString::Length(const Char* Source)
{
	return static_cast<I32>(wcslen(Source));
}
I32		CString::Length(const CharAnsi* Source)
{
	return static_cast<I32>(strlen(Source));
}


Char* CString::Copy(Char* Destination, const Char* Source)
{
	return static_cast <Char*>(wcscpy(Destination, Source));
}
CharAnsi* CString::Copy(CharAnsi* Destination, const CharAnsi* Source)
{
	return static_cast <CharAnsi*>(strcpy(Destination, Source));
}


F32 CString::Atof(const CharAnsi* Str)
{
	return (F32)atof(Str);
}
I32 CString::Atoi(const CharAnsi* Str)
{
	return atoi(Str);
}
I128 CString::Atoll(const CharAnsi* Str)
{
	return atoll(Str);
}

I32 CString::Compare(const CharAnsi* Source1, const CharAnsi* Source2)
{
	return strcmp(Source1, Source2);
}
I32 CString::Compare(const CharAnsi* Source1, const CharAnsi* Source2, I32 Count)
{
	return strncmp(Source1, Source2, Count);
}
I32 CString::CompareCaseInSensitive(const CharAnsi* Source1, const CharAnsi* Source2)
{
	return _strcmpi(Source1, Source2);
}
I32 CString::CompareCaseInSensitive(const CharAnsi* Source1, const CharAnsi* Source2, I32 Count)
{
	return _strnicmp(Source1, Source2, Count);
}



I32 CString::Compare(const Char* Source1, const Char* Source2)
{
	return wcscmp(Source1, Source2);
}
I32 CString::Compare(const Char* Source1, const Char* Source2, I32 Count)
{
	return wcsncmp(Source1, Source2, Count);
}
I32 CString::CompareCaseInSensitive(const Char* Source1, const Char* Source2)
{
	return _wcsicmp(Source1, Source2);
}
I32 CString::CompareCaseInSensitive(const Char* Source1, const Char* Source2, I32 Count)
{
	return _wcsnicmp(Source1, Source2, Count);
}
	

const CharAnsi* CString::Find(const CharAnsi* Source1, const CharAnsi* SubStr)
{
	return strstr(Source1, SubStr);
}

const Char* CString::Find(const Char* Source1, const Char* Source2)
{
	return wcsstr(Source1, Source2);
}


	
const CharAnsi* CString::FindCaseInSensitive(const CharAnsi*, const CharAnsi*)
{
	return "";

}
const Char* CString::FindCaseInSensitive(const Char*, const Char*)
{
	return L"";

}



void CString::ConvertAnsiToWide(const CharAnsi* From, Char* To, I32 Length)
{
	mbstowcs(To, From, Length);
}
void CString::ConvertWideToAnsi(const Char* From, CharAnsi* To, I32 Length)
{
	wcstombs(To, From, Length);
}
#undef _CRT_SECURE_NO_WARNINGS