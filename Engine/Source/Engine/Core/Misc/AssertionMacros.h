#include "Debug.h"

#define Check(expr) if(!(expr)) { FDebug::AssertFailed(#expr, __FILE__, __LINE__, "");}
