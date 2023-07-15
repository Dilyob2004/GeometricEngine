#ifndef WINDOWSSCOPELOCKED_H
#define WINDOWSSCOPELOCKED_H
#include <Engine/Core/Config.h>
#include <Windows.h>
class WindowsCriticalSection
{
public:
	FORCEINLINE WindowsCriticalSection()
	{
		InitializeCriticalSection(&CriticalSection);
		SetCriticalSectionSpinCount(&CriticalSection, 4000);

	}
	FORCEINLINE ~WindowsCriticalSection()
	{
		DeleteCriticalSection(&CriticalSection);
	}


	FORCEINLINE void Lock()
	{
		if (!TryLock())
			EnterCriticalSection(&CriticalSection);
	}
	FORCEINLINE bool TryLock()
	{
		return TryEnterCriticalSection(&CriticalSection);
	}
	FORCEINLINE void UnLock()
	{
		LeaveCriticalSection(&CriticalSection);
	}


private:
	CRITICAL_SECTION CriticalSection;
};
#endif // !WINDOWSSCOPELOCKED_H
