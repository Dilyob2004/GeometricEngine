#ifndef PAIR_H
#define PAIR_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
	template<typename FirstType, typename SecondType>
	class TPair
	{
	public:
		FORCEINLINE TPair()
		{
		}
		FORCEINLINE TPair(const FirstType& Key, const SecondType& Value) 
			: First(Key)
			, Second(Value)
		{
		}
		FORCEINLINE bool operator == (const TPair& Other) const
		{
			return First == Other.First && Second == Other.Second;
		}
		FORCEINLINE bool operator != (const TPair& Other) const
		{
			return !(*this == Other);
		}

		FirstType	First;
		SecondType	Second;
	};
}
#endif // !PAIR_H
