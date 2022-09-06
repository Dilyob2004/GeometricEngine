#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <Engine/Core/Layer.h>
#include <Engine/Core/Config.h>
#include <vector>

namespace MeteorEngine
{
    class METEOR_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();
        void PushLayer(Layer *layer);
        void PushOverlay(Layer * Overlay);


        void PopLayer(Layer *layer);
        void PopOverlay(Layer * Overlay);

        std::vector <Layer*>::iterator begin() {return m_Layers.begin();}
        std::vector <Layer*>::iterator end() {return m_Layers.end();}

    private:
        std::vector <Layer*> m_Layers;
        std::vector <Layer*>::iterator m_LayerInsert;



    };
}

#endif // LAYERSTACK_H
