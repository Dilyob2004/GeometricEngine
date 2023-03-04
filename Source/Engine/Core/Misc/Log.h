#ifndef LOG_H
#define LOG_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{

	enum class TypeLogConsole
	{
		Warning,
		Error,
		Fatal,
		Log
	};
	class GEOMETRIC_API LogConsole
	{
	public:
		static void Msg(const CHAR* );
		static void MsgFormat(const CHAR*, const CHAR*);
		static void MsgFormatArgs(const CHAR*, ...);
	};


	#define LOG(x)	LogConsole::Msg(x)

}
#endif // !LOG_H
