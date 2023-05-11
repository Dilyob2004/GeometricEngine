#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Containers/Array.h>
namespace GeometricEngine
{
	class GEOMETRIC_API ImageWrapper
	{
	public:

		static bool Load(const String&, TVector<U8>&, U32&, U32&);
	};
}

#endif // IMAGEWRAPPER_H
