
#include <Engine/System/Time.h>
namespace MeteorEngine
{
    const Time Time::Zero;



    Time::Time() :
    m_microseconds(0)
    {
    }

    f32 Time::GetSeconds() const
    {
        return m_microseconds / 1000000.f;
    }

    s32 Time::GetMilliseconds() const
    {
        return static_cast<s32>(m_microseconds / 1000);
    }



    s64 Time::GetMicroseconds() const
    {
        return m_microseconds;
    }



    Time::Time(s64 microseconds) :
    m_microseconds(microseconds)
    {
    }

    Time Seconds(f32 amount)
    {
        return Time(static_cast<s64>(amount * 1000000));
    }



    Time Milliseconds(s32 amount)
    {
        return Time(static_cast<s64>(amount) * 1000);
    }



    Time Microseconds(s64 amount)
    {
        return Time(amount);
    }



    bool operator ==(Time left, Time right)
    {
        return left.GetMicroseconds() == right.GetMicroseconds();
    }



    bool operator !=(Time left, Time right)
    {
        return left.GetMicroseconds() != right.GetMicroseconds();
    }



    bool operator <(Time left, Time right)
    {
        return left.GetMicroseconds() < right.GetMicroseconds();
    }



    bool operator >(Time left, Time right)
    {
        return left.GetMicroseconds() > right.GetMicroseconds();
    }



    bool operator <=(Time left, Time right)
    {
        return left.GetMicroseconds() <= right.GetMicroseconds();
    }



    bool operator >=(Time left, Time right)
    {
        return left.GetMicroseconds() >= right.GetMicroseconds();
    }



    Time operator -(Time right)
    {
        return Microseconds(-right.GetMicroseconds());
    }



    Time operator +(Time left, Time right)
    {
        return Microseconds(left.GetMicroseconds() + right.GetMicroseconds());
    }



    Time& operator +=(Time& left, Time right)
    {
        return left = left + right;
    }



    Time operator -(Time left, Time right)
    {
        return Microseconds(left.GetMicroseconds() - right.GetMicroseconds());
    }



    Time& operator -=(Time& left, Time right)
    {
        return left = left - right;
    }



    Time operator *(Time left, f32 right)
    {
        return Seconds(left.GetSeconds() * right);
    }



    Time operator *(Time left, s64 right)
    {
        return Microseconds(left.GetMicroseconds() * right);
    }



    Time operator *(f32 left, Time right)
    {
        return right * left;
    }



    Time operator *(s64 left, Time right)
    {
        return right * left;
    }



    Time& operator *=(Time& left, f32 right)
    {
        return left = left * right;
    }



    Time& operator *=(Time& left, s64 right)
    {
        return left = left * right;
    }



    Time operator /(Time left, f32 right)
    {
        return Seconds(left.GetSeconds() / right);
    }



    Time operator /(Time left, s64 right)
    {
        return Microseconds(left.GetMicroseconds() / right);
    }



    Time& operator /=(Time& left, f32 right)
    {
        return left = left / right;
    }



    Time& operator /=(Time& left, s64 right)
    {
        return left = left / right;
    }



    f32 operator /(Time left, Time right)
    {
        return left.GetSeconds() / right.GetSeconds();
    }



    Time operator %(Time left, Time right)
    {
        return Microseconds(left.GetMicroseconds() % right.GetMicroseconds());
    }



    Time& operator %=(Time& left, Time right)
    {
        return left = left % right;
    }
}
