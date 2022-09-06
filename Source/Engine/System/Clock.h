#ifndef CLOCK_H
#define CLOCK_H
#include <Engine/System/Time.h>
namespace MeteorEngine
{
    class METEOR_API Clock
    {
    public:
        Clock();
        Time GetTime() const;
        Time Restart();

    private:
        Time m_startTime;
    };
}

#endif // CLOCK_H
