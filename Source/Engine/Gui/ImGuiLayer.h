#ifndef IMGUILAYER_H
#define IMGUILAYER_H
#include <Engine/Core/Event.h>
#include <Engine/Core/Layer.h>
namespace MeteorEngine
{
    class METEOR_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void OnAttach() override;
        void OnDetach() override;
        void OnTick() override;

		static void OnEnableHighDpi();
        static void OnBegin();
        static void OnEnd();
        void OnEvent(Event& ) override;
    };
}

#endif // IMGUILAYER_H
