#ifndef SCOPELOCKED_H
#define SCOPELOCKED_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Windows/WindowsCriticalSection.h>
namespace GeometricEngine
{
	typedef WindowsCriticalSection CriticalSection;
	class ScopeLock
	{
	public:
		ScopeLock(CriticalSection* Section)
			: Locker(Section)
		{
			Locker->Lock();
		}
		virtual ~ScopeLock()
		{
			Locker->UnLock();
		}
	private:
		CriticalSection* Locker;

	};
}
#endif // !SCOPELOCKED_H
