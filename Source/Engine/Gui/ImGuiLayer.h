#ifndef IMGUILAYER_H
#define IMGUILAYER_H
#include <Engine/Core/Event.h>
#include <Engine/Core/Layer.h>
#include <Engine/Math/Vector3.h>
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
		static void DrawElem3Controls(const std::string&, Vector3f&, float resetValue = 0.0f, float columnWidth = 100.0f);
		static void OnEnableHighDpi();
        static void OnBegin();
        static void OnEnd();
        void OnEvent(Event& ) override;
    };
}

#endif // IMGUILAYER_H
