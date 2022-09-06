#ifndef EXAMPLELAYER_H
#define EXAMPLELAYER_H
#include "../Engine/Core/Layer.h"
#include <Engine/Render/CameraController2D.h>
#include <Engine/System/Clock.h>
namespace MeteorEngine
{
    class ExampleLayer : public Layer
    {
    public:
        ExampleLayer();
        ~ExampleLayer();
        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event &);


    private:

		Clock								m_clock;
		CameraController2D					m_cameraController;
    };
}
#endif // EXAMPLELAYER_H
