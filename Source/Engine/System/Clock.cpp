#include <Engine/System/Clock.h>
#include <Engine/Platform/Platform.h>
namespace MeteorEngine
{
    Clock::Clock() :
    m_startTime(Platform::GetTime())
    {
    }


    Time Clock::GetTime() const
    {
        return Platform::GetTime() - m_startTime;
    }

    Time Clock::Restart()
    {
        Time now = Platform::GetTime();
        Time elapsed = now - m_startTime;
        m_startTime = now;
        return elapsed;
    }
}
