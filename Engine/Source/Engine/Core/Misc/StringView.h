#ifndef STRINGVIEW_H
#define STRINGVIEW_H
#include "CString.h"
#include <Engine/Core/Misc/AssertionMacros.h> 
class StringView
{
public:
	StringView()
		: Data(nullptr)
		, Length(0)
	{
	}
	StringView(const CharAnsi* InData, I32 InSize)
		: Data(InData)
		, Length(InSize)
	{
	}
	StringView(const StringView& Str)
		: Data(Str.Data)
		, Length(Str.Length)
	{
	}
	StringView(const CharAnsi* InData)
		: Data(InData)
		, Length(CString::Length(InData))
	{
	}
	~StringView()
	{
		Data = nullptr;
	}

	I32 Compare(const StringView& Other, ESearchCase Case = ESearchCase::Sensitive)
	{
		return (Case == ESearchCase::Sensitive) ?
			CString::Compare(**this, *Other) :
			CString::CompareCaseInSensitive(**this, *Other);
	}
	I32 Find(CharAnsi c)
	{
		const CharAnsi* RESTRICT First = Pointer();
		for (const CharAnsi* RESTRICT i = First, *RESTRICT End = i + Size(); i != End; i++)
			if (*i == c)
				return static_cast<I32>(i - First);

		return -1;
	}
	I32 FindLast(CharAnsi c)
	{
		const CharAnsi* RESTRICT Last = Pointer() + Size();
		for (const CharAnsi* RESTRICT i = Last, *RESTRICT First = i - Size(); i != First;) {
			i--;
			if (*i == c)
				return static_cast<I32>(i - First);
		}
		return -1;
	}
	bool StartWith(CharAnsi c, ESearchCase SearchCase = ESearchCase::Sensitive)
	{
		if (SearchCase == ESearchCase::InSensitive)
			return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[0]));

		return Size() > 0 && Data[0] == c;
	}
	bool EndWith(CharAnsi c, ESearchCase SearchCase = ESearchCase::Sensitive)
	{
		if (SearchCase == ESearchCase::InSensitive)
			return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[Size() - 1]));

		return Size() > 0 && Data[Size() - 1] == c;
	}
	bool StartWith(const StringView& Str, ESearchCase SearchCase = ESearchCase::Sensitive)
	{
		if (Str.IsEmpty() || Size() < Str.Size())
			return false;

		if (SearchCase == ESearchCase::InSensitive)
			return CString::CompareCaseInSensitive(Pointer(), *Str, Str.Size()) == 0;

		return CString::Compare(Pointer(), *Str, Str.Size()) == 0;
	}
	bool EndWith(const StringView& Str, ESearchCase SearchCase = ESearchCase::Sensitive)
	{
		if (Str.IsEmpty() || Size() < Str.Size())
			return false;

		if (SearchCase == ESearchCase::InSensitive)
			return CString::CompareCaseInSensitive(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;

		return CString::Compare(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;
	}
	FORCEINLINE const CharAnsi& operator[](I32 Index) const
	{
		Check(Index >= 0 && Index <= Length);
		return Data[Index];
	}

	FORCEINLINE bool IsEmpty() const
	{
		return Length == 0;
	}

	FORCEINLINE bool NotEmpty() const
	{
		return Length != 0;
	}
	FORCEINLINE const CharAnsi* Pointer() const
	{
		return Data;
	}
	FORCEINLINE I32 Size() const
	{
		return Length;
	}


	FORCEINLINE constexpr const CharAnsi* operator*() const
	{
		return Data;
	}

public:

	FORCEINLINE StringView& operator = (const StringView& Other)
	{
		if (*this != Other)
		{
			Data = Other.Data;
			Length = Other.Length;
		}
		return *this;
	}
	FORCEINLINE bool operator == (const StringView& Other) const
	{
		return Length == Other.Length && (CString::Compare(Data, Other.Data) == 0);
	}
	FORCEINLINE bool operator != (const StringView& Other) const
	{
		return !(*this == Other);
	}
	FORCEINLINE bool operator == (const CharAnsi* Other) const
	{
		return *this == Other;
	}
	FORCEINLINE bool operator != (const CharAnsi* Other) const
	{
		return !(*this == Other);
	}
protected:
	const CharAnsi* Data;
	I32 Length;
};
#endif // !STRINGVIEW_H
