#include "Debug.h"
//#include <Windows.h>
//#include <crtdbg.h>

void FDebug::AssertFailed(const CharAnsi* Expr, const CharAnsi* File, I32 Line, const CharAnsi* Format)
{
		/*CharAnsi* Buffer[1024];

		va_list ArgumentList;
		va_start(ArgumentList, Format);
		//_VCrtDbgReportA(_CRT_ASSERT, Buffer, File, Line, NULL, Format, ArgumentList);
		va_end(ArgumentList);
		*/
	//_CrtDbgReport(_CRT_ASSERT, File, Line, NULL, "%ls", Format);
	//__debugbreak();
}