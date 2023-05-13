#ifndef MEMORY_H
#define MEMORY_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
	template<bool Predicate, typename Result = void>
	struct TEnableIf;

	template<typename Result>
	struct TEnableIf<true, Result>
	{
		typedef Result Type;
	};

	template<typename Result>
	struct TEnableIf<false, Result>
	{
	};


	template<typename T> struct TRemoveReference { typedef T Type; };
	template<typename T> struct TRemoveReference<T&> { typedef T Type; };
	template<typename T> struct TRemoveReference<T&&> { typedef T Type; };

	template<typename T>
	inline typename TRemoveReference<T>::Type&& MoveTemp(T&& obj)
	{
		return (typename TRemoveReference<T>::Type&&)obj;
	}

	class GEOMETRIC_API SMemory
	{
	public:

		static void* Allocate(U32, U32 Alignment = 16);
		static void		Copy(void*, const void*, U64);
		static void* Zero(void*, U32);
		static void		Set(void* DST, U32 Size, U32 Value);
		static void		Clear(void*, U32);
		static void		Free(void*);
	};
	namespace TMemory 
	{
		template<typename T>
		FORCEINLINE void DestructItems0(T* Destination, I32 Count)
		{
			while (Count--)
			{
				Destination->~T();
				++Destination;
			}
		}
		template<typename T>
		FORCEINLINE void DestructItems(T* Destination, I32 Count)
		{
		}
		template<typename T>
		FORCEINLINE void ConstructItems0(T* Destination, I32 Count)
		{
			while (Count--)
			{
				new (Destination) T();
				++(T * &)Destination;
			}
		}
		template<typename T>
		FORCEINLINE void ConstructItems(T* Destination, I32 Count)
		{
			SMemory::Set(Destination, 0, sizeof(T) * Count);
		}
		template<typename T, typename U>
		FORCEINLINE void ConstructItems0(T* Destination, const U* Source, I32 Count)
		{
			while (Count--)
			{
				new (Destination) T(*Source);
				++(T * &)Destination;
				++Source;
			}
		}

		template<typename T, typename U>
		FORCEINLINE void ConstructItems(T* Destination, const U* Source, I32 Count)
		{
			SMemory::Copy(Destination, Source, Count * sizeof(U));
		}
		template<typename T, typename U>
		FORCEINLINE void MoveItems0(T* Destination, const U* Source, I32 Count)
		{
			while (Count--)
			{
				new (Destination) T((T&&)* Source);
				++(T * &)Destination;
				++Source;
			}
		}
		template<typename T, typename U>
		FORCEINLINE void MoveItems(T* Destination, const U* Source, I32 Count)
		{
			SMemory::Copy(Destination, Source, Count * sizeof(U));
		}

		template<typename T>
		INLINE void Swap(T& a, T& b) noexcept
		{
			T Temp = a;
			a = b;
			b = Temp;
		}
	}

}
#endif // !MEMORY_H
