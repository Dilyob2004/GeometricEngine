#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Containers/Array.h>
class GEOMETRIC_API ImageWrapper
{
public:

	static bool Load(const String&, TArray<U8>&, U32&, U32&);
};

#endif // IMAGEWRAPPER_H
