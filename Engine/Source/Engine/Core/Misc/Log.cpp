#include "Log.h"
#include <stdio.h>
#include <Engine/Core/Generic/Platform.h>
void LogConsole::MsgString(const String& Format)
{
	FTimeItems Items;
	Platform::GetTime(Items);
	String TimeFormat = String::Format("[%d%d:%d%d:%d%d] ", Items.Hour / 10, Items.Hour % 10,
															Items.Minute / 10, Items.Minute % 10, 
															Items.Second / 10, Items.Second % 10);
	printf(*(TimeFormat + Format));
}
void LogConsole::Msg(ELogCategory Category, const String& Format)
{
	String ResultLog;
	switch (Category)
	{
		case ELogCategory::Error:	ResultLog += "Error: "; break;
		case ELogCategory::Warning: ResultLog += "Warning: "; break;
		case ELogCategory::Log:		ResultLog += "Info: "; break;
		default: break;
	}
	ResultLog.Append(Format);

	FTimeItems Items;
	Platform::GetTime(Items);
	String TimeFormat = String::Format("[%d%d:%d%d:%d%d] ", Items.Hour / 10, Items.Hour % 10,
		Items.Minute / 10, Items.Minute % 10,
		Items.Second / 10, Items.Second % 10);

	printf(*(TimeFormat + ResultLog));
}