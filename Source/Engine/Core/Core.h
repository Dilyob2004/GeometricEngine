#ifndef  CORE_H
#define CORE_H
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
	struct CommandLineSpec
	{
		#ifdef METEOR_DEBUG
			int argc;
			char** argv;
		#else
			PSTR lpCmdLine;
		#endif // DEBUG
	};
	class CommandLine
	{
	public:
		CommandLine() = default;
		~CommandLine() = default;

		static bool Parse(const CommandLineSpec&) { return true; }
	};
	METEOR_API int Main(const CommandLineSpec&);
}
#endif // ! CORE_H
