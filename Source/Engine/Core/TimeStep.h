#ifndef TIMESTEP_H
#define TIMESTEP_H
namespace MeteorEngine
{
    class TimeStep
    {
    public:
        TimeStep(f32 time = 0.0f):
            m_time(time)
        {

        }
        operator float() const { return m_time; }
        f32 GetSeconds() { return m_time; }
        f32 GetMilliSeconds() { return m_time * 1000.f; }

    private:
        f32 m_time;
    };
}
#endif // TIMESTEP_H
