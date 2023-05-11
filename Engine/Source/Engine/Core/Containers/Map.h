#ifndef MAP_H
#define MAP_H
#include <Engine/Core/Containers/Pair.h>
#include <Engine/Core/Containers/Array.h>
namespace GeometricEngine
{
	template<typename KeyType, typename ValueType, typename Allocator = HeapAllocator>
	class TMap
	{
	public:
		typedef TPair < KeyType, ValueType> PairType ;
		typedef TVector<PairType, Allocator> MapType;
		typedef TVector<PairType, Allocator >::Iterator IteratorType;
		FORCEINLINE TMap() { }
		FORCEINLINE TMap(const TMap& Copy) : Element(Copy.Element){ }
		FORCEINLINE void Push(const KeyType& Key, const ValueType& Value)
		{
			Element.Push({ Key, Value });
		}
		FORCEINLINE ValueType& operator [] (const KeyType& i)
		{
			return At(i);
		}
		FORCEINLINE const ValueType& operator [] (const KeyType& i) const
		{
			return At(i);
		}
		FORCEINLINE ValueType& At(const KeyType& Key)
		{
			auto* Pair = FindPairKey(Key);
			if (!Pair)
			{
				Element.Push({ Key, ValueType() });
				Pair = &Element[Element.GetCount() - 1];
			}
			return Pair->Second;
		}
		FORCEINLINE const ValueType& At(const KeyType& Key) const
		{
			const auto* Pair = FindPairKey(Key);
			return Pair->Second;
		}
		FORCEINLINE TPair<KeyType, ValueType>* FindPairKey(const KeyType& Key)
		{
			for (auto i : Element)
				if (i.First == Key) {
					auto& Value = i;
					return &Value;
				}
			return NULL;
		}
		FORCEINLINE IteratorType begin() const
		{
			return Element.begin();
		}
		FORCEINLINE IteratorType end() const
		{
			return Element.end();
		}
		PairType& First() const
		{
			return Element.First();
		}
	private:
		MapType Element;
	};
}
#endif // !MAP_H
