#ifndef STRING_H
#define STRING_H

#include <Engine/Core/Config.h>
#include <Engine/Core/Misc/CString.h>
#include <Engine/Core/Generic/Memory.h>
namespace GeometricEngine
{
	template<typename T>
	class GEOMETRIC_API BasicString
	{
	public:
		BasicString() = default;
		BasicString(const BasicString& Str)
		{
			Update(Str.Pointer(), Str.Size());
		}
		BasicString(const T* Str)
		{
			Update(Str, CString::Length(Str));
		}
		BasicString(const T* Str, I32 NewLength)
		{
			Update(Str, NewLength);
		}
		~BasicString()
		{
			SMemory::Free(Data);
		}

		void Update(const T* Str, I32 NewLength)
		{
			if (!Str || NewLength <= 0)
				return;

			if (Length != NewLength)
			{
				SMemory::Free(Data);
				if (NewLength != 0)
				{
					Data = (T*)SMemory::Allocate((NewLength + 1) * sizeof(T));
					Data[NewLength] = 0;
				}
				else
					Data = NULL;
				Length = NewLength;
			}
			SMemory::Copy(Data, Str, NewLength * sizeof(T));
		}
		void Append(const T* Str, I32 Size)
		{
			if (Size == 0)
				return;

			T * OldData = Data;
			I32 OldLength = Length;

			Length += Size;
			Data = (T*)SMemory::Allocate((Length + 1) * sizeof(T));
			SMemory::Copy(Data, OldData, OldLength * sizeof(T));
			SMemory::Copy(Data, Str, Size * sizeof(T));

			Data[Length] = 0;

			SMemory::Free(OldData);
		}
		I32 Compare(const BasicString& Other, ESearchCase Case = ESearchCase::Sensitive)
		{
			return (Case == ESearchCase::Sensitive) ?
				CString::Compare(**this, *Other) :
				CString::CompareCaseInSensitive(**this, *Other);
		}
		I32 Find(T c) const
		{
			const T* RESTRICT First = Pointer();
			for (const T* RESTRICT i = First, *RESTRICT End = i + Size(); i != End; i++)
				if (*i == c)
					return static_cast<I32>(i - First);

			return -1;
		}
		I32 FindLast(T c) const
		{
			const T* RESTRICT Last = Pointer() + Size();
			for (const T* RESTRICT i = Last, *RESTRICT First = i - Size(); i != First;) {
				i--;
				if (*i == c)
					return static_cast<I32>(i - First);
			}

			return -1;
		}
		I32 Find(const T * Str, ESearchCase Case = ESearchCase::Sensitive, U32 StartPosition = -1) const
		{
			if (Str == NULL || !Data)
				return -1;
			if (StartPosition < Size())
				StartPosition = Size();
			const T * First = Data;

			if (StartPosition != -1)
				First += StartPosition;

			const T * Temp = (Case == ESearchCase::InSensitive) ?
				CString::FindCaseInSensitive(First, Str) :
				CString::Find(First, Str);

			return	Temp ? static_cast<I32>(Temp - **this) : -1;
		}
		I32 FindLast(const T * Str, ESearchCase Case = ESearchCase::Sensitive, U32 StartPosition = -1) const
		{
			const I32 SizeOfStr = CString::Length(Str);
			if (Str == NULL || !Data)
				return -1;
			if (StartPosition == -1)
				StartPosition = Size();
			const T * First = Data;
			for (I32 i = StartPosition - SizeOfStr; i >= 0; i--)
			{
				if (Case == ESearchCase::InSensitive ? CString::CompareCaseInSensitive(Data, Str, SizeOfStr)
					: CString::Compare(Data, Str, SizeOfStr) == 0)
					return i;
			}

			return -1;
		}
		I32 Find(const BasicString & Str, ESearchCase Case = ESearchCase::Sensitive, U32 StartPosition = -1)
		{
			return Find(Str.Pointer(), Case, StartPosition);
		}
		I32 FindLast(const BasicString & Str, ESearchCase Case = ESearchCase::Sensitive, U32 StartPosition = -1)
		{
			return FindLast(Str.Pointer(), Case, StartPosition);
		}
		I32 FindIndexOf(T c, I32 Index = 0)
		{
			while (Index < Size())
			{
				if (Data[Index] == c)
					return Index;
				Index++;
			}
			return -1;
		}
		I32 FindIndexOf(const T * Str, I32 Index = 0)
		{
			while (Index < Size())
			{

				const T C = Data[Index];
				const T* S = Str;

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
		bool StartWith(const BasicString & Str, ESearchCase SearchCase = ESearchCase::Sensitive) const
		{
			if (Str.IsEmpty() || Size() < Str.Size())
				return false;

			if (SearchCase == ESearchCase::InSensitive)
				return CString::CompareCaseInSensitive(Pointer(), *Str, Str.Size()) == 0;

			return CString::Compare(Pointer(), *Str, Str.Size()) == 0;
		}
		bool EndWith(const BasicString & Str, ESearchCase SearchCase = ESearchCase::Sensitive) const
		{
			if (Str.IsEmpty() || Size() < Str.Size())
				return false;

			if (SearchCase == ESearchCase::InSensitive)
				return CString::CompareCaseInSensitive(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;

			return CString::Compare(&(*this)[Size() - Str.Size()], *Str, Str.Size()) == 0;
		}
		BasicString Replace(const T* From, const T* To, ESearchCase Case = ESearchCase::Sensitive)
		{
			return 0;
		}
		
		
		
		void Resize(I32 NewLength)
		{
			const T* OldData = Data;
			const I32 MinLength = min(NewLength, Length);
			Length = NewLength;
			Data = (T*)SMemory::Allocate((Length + 1) * sizeof(T));
			SMemory::Copy(Data, OldData, MinLength * sizeof(T));
			Data[Length] = 0;
			SMemory::Free((T*)OldData);
		}
		
		
		
		void Clear()
		{
			SMemory::Free(Data);
			Data = NULL;
			Length = 0;

		}
		FORCEINLINE T& operator[](I32 Index)
		{
			_ASSERT(Index >= 0 && Index <= Length);
			return Data[Index];
		}
		FORCEINLINE const T& operator[](I32 Index) const
		{
			_ASSERT(Index >= 0 && Index <= Length);
			return Data[Index];
		}
		void Append(const BasicString& Str)
		{
			Append(Str.Pointer(), Str.Size());
		}


		FORCEINLINE bool IsEmpty() const
		{
			return Length == 0;
		}

		FORCEINLINE bool NotEmpty() const
		{
			return Length != 0;
		}
		FORCEINLINE T* Pointer()
		{
			return Data ? Data : "";
		}
		FORCEINLINE const T* Pointer() const
		{
			return Data ? Data : "";
		}
		FORCEINLINE I32 Size() const
		{
			return Length;
		}
		FORCEINLINE BasicString& operator += (const BasicString& Str)
		{
			Append(Str.Pointer(), Str.Size());
			return *this;
		}
		FORCEINLINE BasicString& operator += (const T* Str)
		{
			Append(Str, CString::Length(Str));
			return *this;
		}
		FORCEINLINE BasicString& operator += (T C)
		{
			Append(&C, 1);
			return *this;
		}
		FORCEINLINE BasicString& operator = (const BasicString& Other)
		{
			if (this != &Other)
				Update(Other.Pointer(), Other.Size());
			return *this;
		}
		BasicString& operator = (const T* Other)
		{
			if (this != &Other)
				Update(Other, CString::Length(Other));
			return *this;
		}
		BasicString& operator = (T Other)
		{
			Update(&Other, 1);
			return *this;
		}
		FORCEINLINE const T* operator*() const
		{
			return Data;
		}
		FORCEINLINE  T* operator*()
		{
			return Data;
		}
	protected:
		
		T* Data = NULL;
		I32 Length = 0;
	};


	typedef BasicString<char> String;
}
#endif // !STRING_H
