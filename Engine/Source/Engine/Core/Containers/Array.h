#ifndef ARRAY_H
#define ARRAY_H
#include <Engine/Core/Misc/Allocator.h>
#include <Engine/Core/Misc/AssertionMacros.h>
#include <Engine/Math/MathUtils.h>
#include <initializer_list>
template<typename T, typename Allocator = HeapAllocator>
class TArray
{
public:

	typedef typename Allocator::template Element<T> ElementType;

public:

	FORCEINLINE TArray() :
		ArrayCount(0),
		ArrayMax(0)
	{
	}

	FORCEINLINE TArray(I32 ArrayMaxArray) :
		ArrayCount(0),
		ArrayMax(ArrayMaxArray)
	{
		if (ArrayMaxArray > 0)
			ElementAllocatorType.Allocate(ArrayMax);
	}

	FORCEINLINE TArray(const TArray& Other)
	{
		ArrayMax = ArrayCount = Other.ArrayCount;
		if (ArrayMax > 0)
		{
			ElementAllocatorType.Allocate(ArrayMax);
			TMemory::ConstructItems(ElementAllocatorType.GetAllocation(), Other.ElementAllocatorType.GetAllocation(), Other.ArrayCount);
		}
	}

	TArray(TArray&& Other) noexcept :
		ArrayCount(Other.ArrayCount),
		ArrayMax(Other.ArrayMax)
	{
		Other.ArrayCount = Other.ArrayMax = 0;
		ElementAllocatorType.Swap(Other.ElementAllocatorType);
	}

	FORCEINLINE TArray(const T* Data, I32 ArrayMaxArray) :
		ArrayCount(ArrayMaxArray),
		ArrayMax(ArrayMaxArray)
	{
		if (ArrayMaxArray > 0)
		{
			ElementAllocatorType.Allocate(ArrayMaxArray);
			TMemory::ConstructItems(ElementAllocatorType.GetAllocation(), Data, ArrayMaxArray);
		}
	}

	FORCEINLINE TArray(std::initializer_list<T> ListData)
	{
		ArrayCount = ArrayMax = (I32)ListData.size();
		if (ArrayMax > 0)
		{
			ElementAllocatorType.Allocate(ArrayMax);
			TMemory::ConstructItems(ElementAllocatorType.GetAllocation(), ListData.begin(), ArrayMax);
		}
			
	}

	FORCEINLINE ~TArray()
	{
		TMemory::DestructItems(ElementAllocatorType.GetAllocation(), ArrayCount);
	}



private:
	void Relocate(I32 NewArrayMax)
	{
		if (ArrayMax == NewArrayMax)
			return;

		Check(NewArrayMax >= 0);

		I32 NewCount = MIN(ArrayCount, NewArrayMax);
		ElementAllocatorType.ResizeAllocation(NewArrayMax, ArrayCount, NewCount);
		ArrayMax = NewArrayMax;
		ArrayCount = NewCount;
	}
	void ResizeArrayMax(I32 NewArrayMax)
	{
		if (ArrayMax < NewArrayMax)
			Relocate(ElementAllocatorType.CalculateSizeBlock(ArrayMax, NewArrayMax));
	}
public:

	FORCEINLINE void Push(const T& Element)
	{

		ResizeArrayMax(ArrayCount + 1);
		TMemory::ConstructItems(ElementAllocatorType.GetAllocation() + ArrayCount, &Element, 1);		
		ArrayCount++;
	}
	FORCEINLINE void Push(const T* Elements, I32 Count)
	{

		ResizeArrayMax(ArrayCount + Count);
		TMemory::ConstructItems(ElementAllocatorType.GetAllocation() + ArrayCount, &Elements, Count);
		ArrayCount += Count;
	}

	T Pop()
	{
		T Element(Last());
		PopBack();
		return Element;
	}

	void PopBack()
	{
		--ArrayCount;
		TMemory::DestructItems(ElementAllocatorType.GetAllocation() + ArrayCount, 1);
	}

	void Resize(I32 NewArrayMax)
	{
		if (ArrayCount > NewArrayMax)
			TMemory::DestructItems(ElementAllocatorType.GetAllocation() + NewArrayMax, ArrayCount - NewArrayMax);
		else
		{
			ResizeArrayMax(NewArrayMax + 1);
			TMemory::ConstructItems(ElementAllocatorType.GetAllocation() + ArrayCount, NewArrayMax - ArrayCount);
		}
		ArrayCount = NewArrayMax;
	}


	void RemoveAt(I32 Index)
	{
		Check(Index >= 0 && Index < ArrayCount);
		ArrayCount--;
		T* NewData = ElementAllocatorType.GetAllocation();
		if (ArrayCount)
			NewData[Index] = NewData[ArrayCount];

		TMemory::DestructItems(NewData + ArrayCount, 1);
	}

	void RemoveAtKeepOrder(I32 Index)
	{
		Check(Index >= 0 && Index < ArrayCount);

		ArrayCount--;
		T * NewData = ElementAllocatorType.GetAllocation();


		if (Index < ArrayCount) 
		{
			T* Dst = NewData + Index;
			T* Src = NewData + (Index + 1);
			I32 NewArrayCount = ArrayCount - Index;

			for (int i = 0; i < NewArrayCount; i++)
				Dst[i] = MoveTemp(Src[i]);
		}
		TMemory::DestructItems(NewData + ArrayCount, 1);
	}

	void RemoveAll(const T& Element)
	{
		for (int i = ArrayCount - 1; i >= 0; i--)
			if (ElementAllocatorType.GetAllocation()[i] == Element)
			{
				RemoveAt(i);
				if (IsEmpty())
					break;
			}
	}
	void Swap(TArray& Other)
	{
		TMemory::Swap(ArrayCount, Other.ArrayCount);
		TMemory::Swap(ArrayMax, Other.ArrayMax);
		ElementAllocatorType.Swap(Other.ElementAllocatorType);
	}
	FORCEINLINE void Clear()
	{
		TMemory::DestructItems(ElementAllocatorType.GetAllocation(), ArrayCount);
		ArrayCount = 0;
	}


public:
	template<typename U>
	FORCEINLINE bool Find(const U& Element, I32& Index) const
	{
		Index = Find(Element);
		return Index != -1;
	}
	template<typename U>
	FORCEINLINE bool Find(const U& Element) const
	{
		if (ArrayCount > 0)
		{
			const T* RESTRICT FirstPointer = ElementAllocatorType.GetAllocation();
			for (const T * RESTRICT i	= FirstPointer,  *RESTRICT End	= FirstPointer + ArrayCount; i != End; ++i)
				if (*i == Element)
					return static_cast<int>(i - FirstPointer);
					
		}
		return -1;
	}


public:

	FORCEINLINE T& First()
	{
		return ElementAllocatorType.GetAllocation()[0];
	}
	FORCEINLINE const T& First() const
	{
		return ElementAllocatorType.GetAllocation()[0];
	}

	FORCEINLINE T& Last()
	{
		return ElementAllocatorType.GetAllocation()[ArrayCount - 1];
	}
	FORCEINLINE const T& Last() const
	{
		return ElementAllocatorType.GetAllocation()[ArrayCount - 1];
	}


public:
	FORCEINLINE T& At(I32 Index)
	{
		Check(Index >= 0 && Index < ArrayCount);
		return ElementAllocatorType.GetAllocation()[Index];
	}

	FORCEINLINE const T& At(I32 Index) const
	{
		Check(Index >= 0 && Index < ArrayCount);
		return ElementAllocatorType.GetAllocation()[Index];
	}
	FORCEINLINE T& operator [] (I32 Index)
	{
		Check(Index >= 0 && Index < ArrayCount);
		return ElementAllocatorType.GetAllocation()[Index];
	}
	FORCEINLINE const T& operator [] (I32 Index) const
	{
		Check(Index >= 0 && Index < ArrayCount);
		return ElementAllocatorType.GetAllocation()[Index];
	}
public:
	FORCEINLINE bool IsEmpty() const 
	{ 
		return ArrayCount == 0;
	}

	FORCEINLINE bool NotEmpty() const
	{
		return ArrayCount != 0;
	}
	FORCEINLINE T* Pointer() 
	{
		return ElementAllocatorType.GetAllocation();  
	}
	FORCEINLINE const T* Pointer() const 
	{ 
		return ElementAllocatorType.GetAllocation();  
	}
	FORCEINLINE I32 Count() const 
	{ 
		return ArrayCount; 
	}
	FORCEINLINE I32 SizeMax() const 
	{ 
		return ArrayMax; 
	}
public:
	TArray& operator=(const TArray& Other) noexcept
	{
		if (this != &Other)
		{
			TMemory::DestructItems(ElementAllocatorType.GetAllocation(), ArrayCount);
			if (ArrayMax < Other.ArrayCount)
			{
				ElementAllocatorType.Free();
				ArrayMax = Other.ArrayCount;
				ElementAllocatorType.Allocate(ArrayMax);
			}
			ArrayCount = Other.ArrayCount;
			TMemory::ConstructItems(ElementAllocatorType.GetAllocation(), Other.Pointer(), ArrayCount);
		}
		return *this;
	}
	TArray& operator=(TArray&& Other) noexcept
	{
		if (this != &Other)
		{
			TMemory::DestructItems(ElementAllocatorType.GetAllocation(), ArrayCount);
			ElementAllocatorType.Free();

			ArrayCount = Other.ArrayCount;
			ArrayMax = Other.ArrayMax;
			ElementAllocatorType.Swap(Other.ElementAllocatorType);

		}
		return *this;
	}
	public:


		bool operator == (const TArray<T, Allocator>& Other) const
		{
			if (ArrayCount != Other.ArrayCount)
				return false;
			else
			{
				const T* Data = ElementAllocatorType.GetAllocation();
				const T* OtherData = Other.ElementAllocatorType.GetAllocation();
				for (int i = 0; i < ArrayCount; i++)
					if (Data[i] != OtherData[i])
						return false;
			}
			return true;
		}


		bool operator != (const TArray<T, Allocator> & Other) const
		{
			return !operator==(Other);
		}

	public:
		struct Iterator
		{
			friend TArray;
		public:
			Iterator()
				: Array(NULL)
				, Index(-1)
			{
			}
			Iterator(TArray* InArray, int StartIndex)
				: Array(InArray)
				, Index(StartIndex)
			{
			}
			Iterator(const TArray* InArray, int StartIndex)
				: Array(const_cast<TArray*>(InArray))
				, Index(StartIndex)
			{
			}

			Iterator(const Iterator& It)
				: Array(It.Array)
				, Index(It.Index)
			{
			}
			Iterator& operator++()
			{
				++Index;
				return *this;
			}
			Iterator& operator--()
			{
				--Index;
				return *this;
			}

			Iterator& operator+=(I32 Offset)
			{
				Index += Offset;
				return *this;
			}
			Iterator& operator-=(I32 Offset)
			{
				Index -= Offset;
				return *this;
			}

			Iterator operator+(I32 Offset) const
			{
				return *this += Offset;
			}
			Iterator operator-(I32 Offset) const
			{
				return *this -= Offset;
			}

			T& operator * ()const
			{
				return Array->Pointer()[Index];
			}
			T* operator -> ()const
			{
				return &Array->Pointer()[Index];
			}
			FORCEINLINE bool operator !() const
			{
				return !(bool) *this;
			}
			int GetIndex() const
			{
				return Index;
			}

			void Reset()
			{
				Index = 0;
			}
			FORCEINLINE friend bool operator == (const Iterator& Left,
				const Iterator& Right)
			{
				return (Left.Array == Right.Array) && (Left.Index == Right.Index);
			}
			FORCEINLINE friend bool operator != (const Iterator& Left,
				const Iterator& Right)
			{
				return !(Right == Left);
			}
		private:
			TArray* Array;
			int Index;
		};


	public:
		FORCEINLINE Iterator begin() const
		{
			return Iterator(this, 0);
		}
		FORCEINLINE Iterator end() const
		{
			return Iterator(this, ArrayCount);
		}
private:
	I32 ArrayCount;
	I32 ArrayMax;
	ElementType ElementAllocatorType;
};


#endif // !ARRAY_H
