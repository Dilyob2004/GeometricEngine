#ifndef DEBUG_H
#define DEBUG_H

#include <Engine/Core/Config.h>


class GEOMETRIC_API FDebug
{
public:

	static void _cdecl AssertFailed(const CharAnsi* Expr, const CharAnsi* File, I32 Line, const CharAnsi* Format);
};

#endif // !DEBUG_H
