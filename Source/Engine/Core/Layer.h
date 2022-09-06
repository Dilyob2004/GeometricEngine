#ifndef LAYER_H
#define LAYER_H
#include <Engine/Core/Event.h>
#include <Engine/Core/Config.h>
#include <string>
namespace MeteorEngine
{
    class METEOR_API Layer
    {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();


        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event &) {}

        inline const std::string& GetName() const {return m_debugName;}
    private:
        std::string m_debugName;
    };
}

#endif // LAYER_H
