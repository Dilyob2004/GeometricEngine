#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <Engine/Core/Config.h>
#include <Engine/Core/Misc/CString.h>
namespace GeometricEngine
{
	template<typename T>
	class GEOMETRIC_API BasicStringView
	{
	public:
		constexpr BasicStringView()
			: Data(NULL)
			, Length(0)
		{
		}
		constexpr BasicStringView(const T* InData, I32 InSize)
			: Data(InData)
			, Length(InSize)
		{
		}
		constexpr BasicStringView(const BasicStringView& Str)
			: Data(Str.Data)
			, Length(Str.Size)
		{
		}
		constexpr BasicStringView(const T* InData)
			: Data(InData)
			, Length(CString::Length(InData))
		{
		}


		I32 Compare(const BasicStringView& Other, ESearchCase Case = ESearchCase::Sensitive)
		{
			return (Case == ESearchCase::Sensitive) ?
				CString::Compare(**this, *Other) :
				CString::CompareCaseInSensitive(**this, *Other);
		}
		I32 Find(T c)
		{
			const T* RESTRICT First = Pointer();
			for (const T* RESTRICT i = First, *RESTRICT End = i + Size(); i != End; i++)
				if (*i == c)
					return static_cast<I32>(i - First);

			return -1;
		}
		I32 FindLast(T c)
		{
			const T* RESTRICT Last = Pointer() + Size();
			for (const T* RESTRICT i = Last, *RESTRICT First = i - Size(); i != First;) {
				i--;
				if (*i == c)
					return static_cast<I32>(i - First);
			}

			return -1;
		}
		bool StartWith(T c, ESearchCase SearchCase = ESearchCase::Sensitive) const
		{
			if (SearchCase == ESearchCase::InSensitive)
				return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[0]));

			return Size() > 0 && Data[0] == c;
		}
		bool EndWith(T c, ESearchCase SearchCase = ESearchCase::Sensitive) const
		{
			if (SearchCase == ESearchCase::InSensitive)
				return Size() > 0 && (CString::ToLower(c) == CString::ToLower(Data[Size() - 1]));

			return Size() > 0 && Data[Size() - 1] == c;
		}
		bool StartWith(const BasicStringView& Str, ESearchCase SearchCase = ESearchCase::Sensitive) const
		{
			if (Str.IsEmpty() || Size() < Str.Size())
				return false;

			if (SearchCase == ESearchCase::InSensitive)
				return CString::CompareCaseInSensitive(Pointer(), *Str, Str.Size()) == 0;

			return CString::Compare(Pointer(), *Str, Str.Size()) == 0;
		}
		bool EndWith(const BasicStringView&  Str, ESearchCase SearchCase = ESearchCase::Sensitive) const
		{
			if (Str.IsEmpty() || Size() < Str.Size())
				return false;

			if (SearchCase == ESearchCase::InSensitive)
				return CString::CompareCaseInSensitive(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;

			return CString::Compare(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;
		}
		FORCEINLINE const T& operator[](I32 Index) const
		{
			_ASSERT(Index >= 0 && Index <= Length);
			return Data[Index];
		}

		FORCEINLINE bool IsEmpty() const
		{
			return Size == 0;
		}

		FORCEINLINE bool NotEmpty() const
		{
			return Size != 0;
		}
		FORCEINLINE T* Pointer()
		{
			return Data;
		}
		FORCEINLINE const T* Pointer() const
		{
			return Data;
		}
		FORCEINLINE I32 Size() const 
		{ 
			return Length;
		}


		FORCEINLINE constexpr const T* operator*() const
		{
			return Data;
		}

	public:

		FORCEINLINE BasicStringView& operator = (const BasicStringView& Other)
		{
			if (*this != Other)
			{
				Data = Other.Data;
				Length = Other.Length;
			}
			return *this;
		}
		FORCEINLINE bool operator == (const BasicStringView& Other) const
		{
			return Length == Other.Length && (CString::Compare(Data, Other.Data) == 0);
		}
		FORCEINLINE bool operator != (const BasicStringView& Other) const
		{
			return !(*this == Other);
		}
		FORCEINLINE bool operator == (const T* Other) const
		{
			return *this == Other;
		}
		FORCEINLINE bool operator != (const T * Other) const
		{
			return !(*this == Other);
		}
	protected:
		const T* Data;
		I32 Length;
	};


	typedef BasicStringView<char> StringView;
	
}
#endif // !STRINGVIEW_H
