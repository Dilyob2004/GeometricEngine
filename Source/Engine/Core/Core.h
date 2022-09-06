#ifndef  CORE_H
#define CORE_H
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
	struct CommandLine
	{
		#ifdef METEOR_DEBUG
			int argc;
			char** argv;
		#else
			PSTR lpCmdLine;
		#endif // DEBUG

	};
	METEOR_API int Main(CommandLine);
}
#endif // ! CORE_H
