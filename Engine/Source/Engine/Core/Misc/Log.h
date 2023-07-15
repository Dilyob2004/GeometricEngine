#ifndef LOG_H
#define LOG_H
#include <Engine/Core/Config.h>
#include "String.h"
enum ELogCategory
{
	Error,
	Warning,
	Log
};
class GEOMETRIC_API LogConsole
{
public:
	static void MsgString(const String&);
	static void Msg(ELogCategory, const String& );
};
static void LOG(const String& Format)
{
	LogConsole::MsgString(Format);
}

static void LOG(ELogCategory Category, const String& Format)
{
	LogConsole::Msg(Category, Format);
}
#endif // !LOG_H
