#ifndef EXAMPLELAYER_H
#define EXAMPLELAYER_H
#include <Engine/Core/Layer.h>
namespace MeteorEngine
{
    class ExampleLayer : public Layer
    {
    public:
        ExampleLayer();
        ~ExampleLayer();
        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnTick();
        virtual void OnEvent(Event &);
    };
}
#endif // EXAMPLELAYER_H
