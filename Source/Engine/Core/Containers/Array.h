#ifndef ARRAY_H
#define ARRAY_H
#include <Engine/Core/Misc/Allocator.h>
namespace GeometricEngine
{

	template<typename T, typename Allocator = HeapAllocator>
	class TVector
	{
	public:
		typedef typename Allocator::template Element<T> ElementType;
	public:
		FORCEINLINE TVector() :
			Count(0),
			Size(0)
		{
		}
		FORCEINLINE TVector(I32 SizeArray) :
			Count(0),
			Size(SizeArray)
		{
			if (SizeArray > 0)
				ElementAllocatorType.Allocate(SizeArray);
		}
		FORCEINLINE TVector(const TVector& Other) :
			Count(Other.Count),
			Size(Other.Size)
		{
			if (Count > 0)
			{
				ElementAllocatorType.Allocate(Count);
				TMemory::ConstructItems(ElementAllocatorType.GetAllocation(), Other.ElementAllocatorType.GetAllocation(), Count);
			}	
		}
		FORCEINLINE TVector(const T* Data, I32 SizeArray) :
			Count(SizeArray),
			Size(SizeArray)
		{
			if (SizeArray > 0)
			{
				ElementAllocatorType.Allocate(SizeArray);
				SMemory::Copy(ElementAllocatorType.GetAllocation(), Data, SizeArray);
			}
		}


		FORCEINLINE ~TVector()
		{
			TMemory::DestructItems(ElementAllocatorType.GetAllocation(), Count);
		}

	public:

		FORCEINLINE void Push(const T& Element)
		{
			ElementAllocatorType.ResizeAllocation(Size, Count, Count+1);
			
			TMemory::ConstructItems(ElementAllocatorType.GetAllocation() + Count, &Element, 1);


			Count++;
			Size++;
		}
		T Pop()
		{
			T Element(Last());
			PopBack();
			return Element;
		}
		void PopBack()
		{
			--Count;
			TMemory::DestructItems(ElementAllocatorType.GetAllocation() + Count, 1);
		}
		void Resize(I32 NewSize)
		{
			if (Count > NewSize)
				TMemory::DestructItems(ElementAllocatorType.GetAllocation() + NewSize, Count - NewSize);
			else
			{
				ElementAllocatorType.ResizeAllocation(NewSize, Count, NewSize);
				TMemory::ConstructItems(ElementAllocatorType.GetAllocation() + Count, NewSize - Count);
			}
			Size = Count = NewSize;
		}


		void RemoveAt(I32 Index)
		{
			_ASSERT(Index >= 0 && Index < Count);
			Count--;
			T* NewData = ElementAllocatorType.GetAllocation();
			if (Count)
				NewData[Index] = NewData[Count];

			TMemory::DestructItems(NewData + Count, 1);
		}

		void RemoveAll(const T& Element)
		{
			for (int i = GetCount() - 1; i >= 0; i--)
				if (ElementAllocatorType.GetAllocation()[i] == Element)
				{
					RemoveAt(i);
					if (IsEmpty())
						break;
				}
		}
		void Swap(TVector& Other)
		{
			TMemory::Swap(Count, Other.Count);
			TMemory::Swap(Size, Other.Size);
			ElementAllocatorType.Swap(Other.ElementAllocatorType);
		}
		FORCEINLINE void Clear()
		{
			TMemory::DestructItems(ElementAllocatorType.GetAllocation(), Count);
			Count = 0;
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
				if (Count > 0)
				{
					const T* RESTRICT FirstPointer = ElementAllocatorType.GetAllocation();
					for (const T * RESTRICT i	= FirstPointer,  *RESTRICT End	= FirstPointer + Count; i != End; ++i)
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
			return ElementAllocatorType.GetAllocation()[Count - 1];
		}
		FORCEINLINE const T& Last() const
		{
			return ElementAllocatorType.GetAllocation()[Count - 1];
		}



		FORCEINLINE T& At(I32 Index)
		{
			C_ASSERT(Index >= 0 && Index < Count);
			return ElementAllocatorType.GetAllocation()[Index];
		}

		FORCEINLINE const T& At(I32 Index) const
		{
			C_ASSERT(Index >= 0 && Index < Count);
			return ElementAllocatorType.GetAllocation()[Index];
		}
	public:
		FORCEINLINE bool IsEmpty() const 
		{ 
			return Count == 0;
		}

		FORCEINLINE bool NotEmpty() const
		{
			return Count != 0;
		}
		FORCEINLINE T* Pointer() 
		{
			return ElementAllocatorType.GetAllocation();  
		}
		FORCEINLINE const T* Pointer() const 
		{ 
			return ElementAllocatorType.GetAllocation();  
		}
		FORCEINLINE I32 GetCount() const 
		{ 
			return Count; 
		}
		FORCEINLINE I32 GetSize() const 
		{ 
			return Size; 
		}
	public:

		bool operator == (const TVector<T, Allocator>& Other) const
		{
			if (Count != Other.Count)
				return false;
			else
			{
				const T* Data = ElementAllocatorType.GetAllocation();
				const T* OtherData = Other.ElementAllocatorType.GetAllocation();
				for (int i = 0; i < Count; i++)
					if (Data[i] != OtherData[i])
						return false;
			}
			return true;
		}


		bool operator != (const TVector<T, Allocator>& Other) const
		{
			return !operator==(Other);
		}
		TVector& operator=(const TVector& Other) noexcept
		{
			if (this != &Other)
			{
				TMemory::DestructItems(ElementAllocatorType.GetAllocation(), Count);
				if (Size < Other.Size)
				{
					ElementAllocatorType.Free();
					Size = Other.GetCount();
					ElementAllocatorType.Allocate(Size);
				}
				TMemory::ConstructItems(ElementAllocatorType.GetAllocation(), Other.Pointer(), Count);

			}
			return *this;
		}
		TVector& operator=(TVector&& Other) noexcept
		{
			if (this != &Other)
			{
				TMemory::DestructItems(ElementAllocatorType.GetAllocation(), Count);
				ElementAllocatorType.Free();

				Count = Other.Count;
				Size = Other.Size;
				ElementAllocatorType.Swap(Other.ElementAllocatorType);

			}
			return *this;
		}
		FORCEINLINE T& operator [] (I32 Index)
		{
			_ASSERT(Index >= 0 && Index < Count);
			return ElementAllocatorType.GetAllocation()[Index];
		}
		FORCEINLINE const T& operator [] (I32 Index) const
		{
			_ASSERT(Index >= 0 && Index < Count);
			return ElementAllocatorType.GetAllocation()[Index];
		}


		public:
			struct Iterator
			{
				friend TVector;
			public:
				Iterator()
					: Array(NULL)
					, Index(-1)
				{
				}
				Iterator(TVector* InArray, int StartIndex)
					: Array(InArray)
					, Index(StartIndex)
				{
				}
				Iterator(const TVector* InArray, int StartIndex)
					: Array(const_cast<TVector*>(InArray))
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
				TVector* Array;
				int Index;
			};


		public:
			FORCEINLINE Iterator begin() const
			{
				return Iterator(this, 0);
			}
			FORCEINLINE Iterator end() const
			{
				return Iterator(this, Count);
			}
	private:
		I32 Count;
		I32 Size;
		ElementType ElementAllocatorType;
	};
}

#endif // !ARRAY_H
