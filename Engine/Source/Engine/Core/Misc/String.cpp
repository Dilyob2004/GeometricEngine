#include "String.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <Engine/Math/MathUtils.h>
void String::Resize(I32 NewLength)
{
	const CharAnsi* OldData = Data;
	const I32 MinLength = MIN(NewLength, Length);

	Length = NewLength;
		
	Data = (CharAnsi*)SMemory::Allocate((Length + 1) * sizeof(CharAnsi));
		
	SMemory::Copy(Data, OldData, MinLength * sizeof(CharAnsi));

	Data[Length] = 0;



	SMemory::Free((CharAnsi*)OldData);
}
void String::Set(const CharAnsi* Str, I32 NewLength)
{
	if (Length != NewLength)
	{
		SMemory::Free(Data);
		if (NewLength != 0)
		{
			Data = (CharAnsi*)SMemory::Allocate((NewLength + 1) * sizeof(CharAnsi));
			Data[NewLength] = 0;
		}
		else
			Data = NULL;
		Length = NewLength;
	}
	SMemory::Copy(Data, Str, NewLength * sizeof(CharAnsi));
}

void String::Append(const CharAnsi * Str, I32 Size)
{
	if (Size == 0)
		return;

	CharAnsi* OldData = Data;
	I32 OldLength = Length;

	Length = OldLength + Size;
	Data = (CharAnsi*)SMemory::Allocate((Length + 1) * sizeof(CharAnsi));

	SMemory::Copy(Data, OldData, OldLength * sizeof(CharAnsi));
	SMemory::Copy(Data + OldLength, Str, Size * sizeof(CharAnsi));

	Data[Length] = 0;

	SMemory::Free(OldData);
}
void String::ReserveUninitialized(I32 NewLength)
{
	if (Length == NewLength)
		return;
	SMemory::Free(Data);
	if (NewLength != 0)
	{
		Data = (CharAnsi*)SMemory::Allocate((NewLength + 1) * sizeof(CharAnsi));
		Data[NewLength] = 0;
	}
	else
	{
		Data = nullptr;
	}
	Length = NewLength;
}
#define _CRT_SECURE_NO_WARNINGS
String String::Format(const CharAnsi* Format, ...)
{

	va_list ArgumentList;
	va_start(ArgumentList, Format);
	CharAnsi szBuffer[1024];
	int nBuf = _vsnprintf_s(szBuffer, _countof(szBuffer), Format, ArgumentList);
	va_end(ArgumentList);
	return String(szBuffer);

}
#undef _CRT_SECURE_NO_WARNINGS
