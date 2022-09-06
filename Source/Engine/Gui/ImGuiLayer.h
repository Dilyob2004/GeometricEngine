#ifndef IMGUILAYER_H
#define IMGUILAYER_H
#include <Engine/Core/Event.h>
#include <Engine/Core/Layer.h>
namespace MeteorEngine
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        static void OnBegin();
        static void OnEnd();
        void OnEvent(Event& ) override;
    };
}

#endif // IMGUILAYER_H
