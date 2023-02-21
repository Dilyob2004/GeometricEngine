#include <Engine/Core/Misc/Log.h>

namespace GeometricEngine
{
	void LogConsole::Msg(const CHAR* text)
	{
		printf("%s", text);
	}
	void LogConsole::MsgFormat(const CHAR* format, const CHAR* text)
	{
		printf(format, text);
	}
	void LogConsole::MsgFormatArgs(const CHAR* format, ...)
	{
		va_list ArgumentList;
		va_start(ArgumentList, format);
		vprintf(format, ArgumentList);
		va_end(ArgumentList);
	}
}