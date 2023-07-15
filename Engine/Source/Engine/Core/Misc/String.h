#ifndef STRING_H
#define STRING_H
#include <Engine/Core/Misc/CString.h>
#include <Engine/Core/Generic/Memory.h>
#include <Engine/Core/Misc/AssertionMacros.h>
#include <Engine/Core/Containers/Array.h>

class String
{
public:
	String() = default;
	String(const CharAnsi* Str) : String()
	{
		Set(Str, CString::Length(Str));
	}
	String(const CharAnsi* Str, I32 NewLength) : String()
	{
		Set(Str, NewLength);
	}
	String(const String& Str) : String()
	{
		Set(Str.Pointer(), Str.Size());
	}
	~String()
	{
		SMemory::Free(Data);
	}

public:

	I32 Compare(const String& Other, ESearchCase Case = ESearchCase::Sensitive)
	{
		return (Case == ESearchCase::Sensitive) ?
			CString::Compare(**this, *Other) :
			CString::CompareCaseInSensitive(**this, *Other);
	}
	I32 Find(CharAnsi c) const
	{
		const CharAnsi* RESTRICT First = Pointer();
		for (const CharAnsi* RESTRICT i = First, *RESTRICT End = i + Size(); i != End; i++)
			if (*i == c)
				return static_cast<I32>(i - First);

		return -1;
	}
	I32 FindLast(CharAnsi c) const
	{
		const CharAnsi* RESTRICT Last = Pointer() + Size();
		for (const CharAnsi* RESTRICT i = Last, *RESTRICT First = i - Size(); i != First;) {
			i--;
			if (*i == c)
				return static_cast<I32>(i - First);
		}

		return -1;
	}
	I32 Find(const CharAnsi* Str, ESearchCase Case = ESearchCase::Sensitive, I32 StartPosition = -1)
	{
		if (Str == nullptr || !Data)
			return -1;

		if (StartPosition < Size())
			StartPosition = Size();

		const CharAnsi* First = Data;

		if (StartPosition != -1)
			First += StartPosition;

		const CharAnsi* Temp = (Case == ESearchCase::InSensitive) ?
			CString::FindCaseInSensitive(First, Str) :
			CString::Find(First, Str);

		return	Temp ? static_cast<I32>(Temp - **this) : -1;
	}
	I32 FindLast(const CharAnsi* Str, ESearchCase Case = ESearchCase::Sensitive, I32 StartPosition = -1)
	{
		const I32 SizeOfStr = CString::Length(Str);
		if (Str == nullptr || !Data)
			return -1;
		if (StartPosition == -1)
			StartPosition = Size();
		const CharAnsi* First = Data;
		for (I32 i = StartPosition - SizeOfStr; i >= 0; i--)
		{
			if (Case == ESearchCase::InSensitive ? CString::CompareCaseInSensitive(Data, Str, SizeOfStr)
				: CString::Compare(Data, Str, SizeOfStr) == 0)
				return i;
		}

		return -1;
	}
	I32 Find(const String& Str, ESearchCase Case = ESearchCase::Sensitive, I32 StartPosition = -1)
	{
		return Find(Str.Pointer(), Case, StartPosition);
	}
	I32 FindLast(const String& Str, ESearchCase Case = ESearchCase::Sensitive, I32 StartPosition = -1)
	{
		return FindLast(Str.Pointer(), Case, StartPosition);
	}
	I32 FindIndexOf(CharAnsi c, I32 Index = 0)
	{
		while (Index < Size())
		{
			if (Data[Index] == c)
				return Index;
			Index++;
		}
		return -1;
	}
	I32 FindIndexOf(const CharAnsi* Str, I32 Index = 0)
	{
		while (Index < Size())
		{

			const CharAnsi C = Data[Index];
			const CharAnsi* S = Str;

			while (*S)
			{
				if (C == *S)
					return Index;
				++S;
			}
			Index++;
		}
		return -1;
	}
	bool StartWith(CharAnsi c, ESearchCase SearchCase = ESearchCase::Sensitive) const
	{
		if (SearchCase == ESearchCase::InSensitive)
			return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[0]));

		return Size() > 0 && Data[0] == c;
	}
	bool EndWith(CharAnsi c, ESearchCase SearchCase = ESearchCase::Sensitive) const
	{
		if (SearchCase == ESearchCase::InSensitive)
			return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[Size() - 1]));

		return Size() > 0 && Data[Size() - 1] == c;
	}
	bool StartWith(const String& Str, ESearchCase SearchCase = ESearchCase::Sensitive) const
	{
		if (Str.IsEmpty() || Size() < Str.Size())
			return false;

		if (SearchCase == ESearchCase::InSensitive)
			return CString::CompareCaseInSensitive(Pointer(), *Str, Str.Size()) == 0;

		return CString::Compare(Pointer(), *Str, Str.Size()) == 0;
	}
	bool EndWith(const String& Str, ESearchCase SearchCase = ESearchCase::Sensitive) const
	{
		if (Str.IsEmpty() || Size() < Str.Size())
			return false;

		if (SearchCase == ESearchCase::InSensitive)
			return CString::CompareCaseInSensitive(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;

		return CString::Compare(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;
	}
	String Replace(const CharAnsi* From, const CharAnsi* To, ESearchCase Case = ESearchCase::Sensitive)
	{
		return 0;
	}
	String SubString(I32 Index) const
	{
		Check(Index >= 0 && Index <= Length-1);
		return String(Data + Index, Length - Index);
	}
	String SubString(I32 Index, I32 Count) const
	{
		Check(Count >= 0 && Index >= 0 && Index + Count <= Length - 1 );
		return String(Data + Index, Count);
	}
	TArray<String> Split(CharAnsi C) const
	{
		TArray<String> Result;
		I32 Start = 0;
		for (int i = 0; i < Length; i++)
		{
			if (Data[i] == C)
			{
				Result.Push(SubString(Start, i - Start));
				Start = i + 1;
			}
		}
		if (Length - Start > 0)
		{
			Result.Push(SubString(Start, Length - Start));
		}
		return Result;
	}
	F32 ToFloat() const
	{
		return CString::Atof(Data);
	}
	I32 ToInt() const
	{
		return CString::Atoi(Data);
	}
	static String Format(const CharAnsi* Buffer, ...);
public:


	void Set(const CharAnsi* Str, I32 NewLength);
	void Resize(I32 NewLength);
	void ReserveUninitialized(I32 NewLength);

	void Clear()
	{
		SMemory::Free(Data);
		Data = nullptr;
		Length = 0;
	}

public:
	FORCEINLINE CharAnsi& operator[](I32 Index)
	{
		Check(Index >= 0 && Index <= Length);
		return Data[Index];
	}
	FORCEINLINE const CharAnsi& operator[](I32 Index) const
	{
		Check(Index >= 0 && Index <= Length);
		return Data[Index];
	}
	void Append(const CharAnsi* Str, I32 Size);

	void Append(CharAnsi C)
	{
		Append(&C, 1);
	}
	void Append(const CharAnsi* Str)
	{
		Append(Str, CString::Length(Str));
	}
	void Append(const String& Str)
	{
		Append(Str.Pointer(), Str.Size());
	}


public:

	FORCEINLINE bool operator == (const String& Other) const
	{
		return (Length == Other.Length) && (CString::Compare(Data, Other.Data) == 0);
	}
	FORCEINLINE bool operator != (const String& Other) const
	{
		return !(*this == Other);
	}


	FORCEINLINE bool operator == (const CharAnsi* OtherData) const
	{
		return (CString::Compare(Data, OtherData) == 0);
	}
	FORCEINLINE bool operator != (const CharAnsi* OtherData) const
	{
		return (CString::Compare(Data, OtherData) != 0);
	}

	FORCEINLINE bool operator < (const String& Other) const
	{
		return (CString::Compare(Data, Other.Data) < 0);
	}
	FORCEINLINE bool operator <= (const String& Other) const
	{
		return (CString::Compare(Data, Other.Data) <= 0);
	}
	FORCEINLINE bool operator > (const String& Other) const
	{
		return (CString::Compare(Data, Other.Data) > 0);
	}
	FORCEINLINE bool operator >= (const String& Other) const
	{
		return (CString::Compare(Data, Other.Data) >= 0);
	}
	FORCEINLINE String& operator += (const String& Str)
	{
		Check(Str.NotEmpty());
		Append(Str.Pointer(), Str.Size());
		return *this;
	}
	FORCEINLINE String& operator += (const CharAnsi* Str)
	{
		Check(Str);
		Append(Str, CString::Length(Str));
		return *this;
	}
	FORCEINLINE String& operator += (CharAnsi C)
	{
		Check(C);
		Append(&C, 1);
		return *this;
	}
	FORCEINLINE String& operator = (const String& Other)
	{
		Check(Other.NotEmpty());
		if (this != &Other)
			Set(Other.Pointer(), Other.Size());
		return *this;
	}
	String& operator = (const CharAnsi* Other)
	{
		Check(Other);
		if (Data != Other)
			Set(Other, CString::Length(Other));
		return *this;
	}
	String& operator = (CharAnsi Other)
	{
		Check(Other);
		Set(&Other, 1);
		return *this;
	}
public:
	FORCEINLINE String operator + (CharAnsi C)
	{
		Check(C);
		Append(C);
		return *this;
	}


	FORCEINLINE String operator + (const CharAnsi* Str) 
	{
		Check(Str);
		Append(Str);
		return *this;
	}
	FORCEINLINE String operator + (const String& Str) 
	{
		Check(Str.NotEmpty());
		Append(Str);
		return *this;
	}
	FORCEINLINE String& operator /=(const CharAnsi* Str)
	{
		if (Length > 1 && Data[Length-2] != '/' && Data[Length - 2] != '\\')
			*this += "/";

		return *this += Str;
	}
	FORCEINLINE String& operator /=(const String& Str)
	{
		return operator/=( *Str );
	}
	FORCEINLINE String operator /(const CharAnsi* Str) const
	{
		return String(*this) /= Str;
	}
	FORCEINLINE String operator /(const String& Str) const
	{
		return operator/(*Str);
	}
public:

	FORCEINLINE bool IsEmpty() const
	{
		return Length == 0;
	}

	FORCEINLINE bool NotEmpty() const
	{
		return Length != 0;
	}
	FORCEINLINE CharAnsi* Pointer()
	{
		return Data;
	}
	FORCEINLINE const CharAnsi* Pointer() const
	{
		return Data ? Data : "";
	}
	FORCEINLINE I32 Size() const
	{
		return Length;
	}
	FORCEINLINE const CharAnsi* operator*() const
	{
		return Data;
	}
	FORCEINLINE  CharAnsi* operator*()
	{
		return Data;
	}
protected:

	CharAnsi* Data = nullptr;
	I32 Length = 0;
};


#endif // !STRING_H
