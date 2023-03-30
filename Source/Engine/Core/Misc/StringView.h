#ifndef STRINGVIEW_H
#define STRINGVIEW_H
#include <Engine/Core/Misc/CString.h>
namespace GeometricEngine
{
	class StringView
	{
	public:
		StringView()
			: Data(NULL)
			, Length(0)
		{
		}
		StringView(const CHAR* InData, I32 InSize)
			: Data(InData)
			, Length(InSize)
		{
		}
		StringView(const StringView& Str)
			: Data(Str.Data)
			, Length(Str.Length)
		{
		}
		StringView(const CHAR* InData)
			: Data(InData)
			, Length(CString::Length(InData))
		{
		}
		~StringView()
		{
			Data = NULL;
		}

		I32 Compare(const StringView& Other, ESearchCase Case = ESearchCase::Sensitive)
		{
			return (Case == ESearchCase::Sensitive) ?
				CString::Compare(**this, *Other) :
				CString::CompareCaseInSensitive(**this, *Other);
		}
		I32 Find(CHAR c)
		{
			const CHAR* RESTRICT First = Pointer();
			for (const CHAR* RESTRICT i = First, *RESTRICT End = i + Size(); i != End; i++)
				if (*i == c)
					return static_cast<I32>(i - First);

			return -1;
		}
		I32 FindLast(CHAR c)
		{
			const CHAR* RESTRICT Last = Pointer() + Size();
			for (const CHAR* RESTRICT i = Last, *RESTRICT First = i - Size(); i != First;) {
				i--;
				if (*i == c)
					return static_cast<I32>(i - First);
			}

			return -1;
		}
		bool StartWith(CHAR c, ESearchCase SearchCase = ESearchCase::Sensitive)
		{
			if (SearchCase == ESearchCase::InSensitive)
				return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[0]));

			return Size() > 0 && Data[0] == c;
		}
		bool EndWith(CHAR c, ESearchCase SearchCase = ESearchCase::Sensitive)
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
		bool EndWith(const StringView&  Str, ESearchCase SearchCase = ESearchCase::Sensitive)
		{
			if (Str.IsEmpty() || Size() < Str.Size())
				return false;

			if (SearchCase == ESearchCase::InSensitive)
				return CString::CompareCaseInSensitive(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;

			return CString::Compare(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;
		}
		FORCEINLINE const CHAR& operator[](I32 Index) const
		{
			_ASSERT(Index >= 0 && Index <= Length);
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
		FORCEINLINE const CHAR* Pointer() const
		{
			return Data;
		}
		FORCEINLINE I32 Size() const 
		{ 
			return Length;
		}


		FORCEINLINE constexpr const CHAR* operator*() const
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
		FORCEINLINE bool operator == (const CHAR* Other) const
		{
			return *this == Other;
		}
		FORCEINLINE bool operator != (const CHAR* Other) const
		{
			return !(*this == Other);
		}
	protected:
		const CHAR* Data;
		I32 Length;
	};
	
}
#endif // !STRINGVIEW_H
