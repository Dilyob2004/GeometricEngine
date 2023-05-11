#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <Engine/Core/Generic/Memory.h>
namespace GeometricEngine
{



	class HeapAllocator
	{
	public:
		template<typename T>
		class Element
		{
		public:
			FORCEINLINE Element() { }
			FORCEINLINE ~Element() { if (Data) SMemory::Free(Data); }

			FORCEINLINE T*			GetAllocation()			{ return Data; }
			FORCEINLINE const T*	GetAllocation() const	{ return Data;  }

			FORCEINLINE void Allocate(U64 Size)
			{ 
				Data = (T*)SMemory::Allocate(Size * sizeof(T));
			}
			FORCEINLINE I32 CalculateSizeBlock(I32 Size, I32 MinSize)
			{
				if (Size < MinSize) Size = MinSize;

				if (Size < 8)
					return 8;
				Size--;
				Size |= Size >> 1;
				Size |= Size >> 2;
				Size |= Size >> 4;
				Size |= Size >> 8;
				Size |= Size >> 16;
				Size = (Size + 1) * 2;

				return Size;
			}
			FORCEINLINE void ResizeAllocation(U64 Size, U32 OldCount, U32 NewCount)
			{
				T* NewData = (T*)SMemory::Allocate(Size * sizeof(T));
				
				if (OldCount)
				{
					if (NewCount > 0)
						TMemory::MoveItems(NewData, Data, NewCount);
					TMemory::DestructItems(Data, OldCount);
				}

				SMemory::Free(Data);
				Data = NewData;

			}
			FORCEINLINE void Free()
			{
				SMemory::Free(Data);
				Data = NULL;
			}
			FORCEINLINE void Swap(Element& Other)
			{
				TMemory::Swap(Data, Other.Data);
			}
		private:

			T* Data = NULL;
		};
	};
}
#endif // !ALLOCATOR_H
