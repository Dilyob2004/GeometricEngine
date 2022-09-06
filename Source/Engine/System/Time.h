#ifndef TIME_H
#define TIME_H

#include <Engine/Core/Config.h>
namespace MeteorEngine
{
    class METEOR_API Time
    {
    public:
        Time();
        f32 GetSeconds() const;
        s32 GetMilliseconds() const;
        s64 GetMicroseconds() const;
        static const Time Zero;
    private:
        friend METEOR_API Time Seconds(f32);
        friend METEOR_API Time Milliseconds(s32);
        friend METEOR_API Time Microseconds(s64);
        explicit Time(s64 microseconds);

    private:

        s64 m_microseconds;
    };

    METEOR_API Time Seconds(f32 amount);
    METEOR_API Time Milliseconds(s32 amount);
    METEOR_API Time Microseconds(s64 amount);
    METEOR_API bool operator ==(Time left, Time right);
    METEOR_API bool operator !=(Time left, Time right);
    METEOR_API bool operator <(Time left, Time right);
    METEOR_API bool operator >(Time left, Time right);
    METEOR_API bool operator <=(Time left, Time right);
    METEOR_API bool operator >=(Time left, Time right);
    METEOR_API Time operator -(Time right);
    METEOR_API Time operator +(Time left, Time right);
    METEOR_API Time& operator +=(Time& left, Time right);
    METEOR_API Time operator -(Time left, Time right);
    METEOR_API Time& operator -=(Time& left, Time right);
    METEOR_API Time operator *(Time left, f32 right);
    METEOR_API Time operator *(Time left, s64 right);
    METEOR_API Time operator *(f32 left, Time right);
    METEOR_API Time operator *(s64 left, Time right);
    METEOR_API Time& operator *=(Time& left, f32 right);
    METEOR_API Time& operator *=(Time& left, s64 right);
    METEOR_API Time operator /(Time left, f32 right);
    METEOR_API Time operator /(Time left, s64 right);
    METEOR_API Time& operator /=(Time& left, f32 right);
    METEOR_API Time& operator /=(Time& left, s64 right);
    METEOR_API f32 operator /(Time left, Time right);
    METEOR_API Time operator %(Time left, Time right);
    METEOR_API Time& operator %=(Time& left, Time right);

}


#endif // TIME_H

