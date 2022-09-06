
#include <Engine/Core/Application.h>
#include <Engine/Core/Input.h>
#include <Engine/Gui/ImGuiLayer.h>

#include <Engine/Render/Renderer.h>
#include <Editor/Editor.h>
#include <Editor/ExampleLayer.h>
#include <Engine/Platform/Platform.h>

#include <Engine/Platform/Win32/OpenGLSupport.h>
namespace MeteorEngine
{
    Application* Application::m_instance = NULL;
    Application::Application()
    {
        m_instance  = this;
        m_window    = std::unique_ptr<Window>( Window::Create("Meteor Engine, OpenGL Build 4.3.0", Vector2u(1280, 720) ) );
        m_context   = std::unique_ptr<OpenGLContext>(OpenGLContext::Create(m_window.get()));

        m_context->SetVSync(true);

        RendererCommand::InitEngine();


        PushLayer(new ImGuiLayer());
        PushLayer(new Editor());
    }
    Application::~Application()
    {
        for(auto i = m_layerStack.begin(); i != m_layerStack.end(); i++)
            (*i)->OnDetach();

    }
    u32 Application::GetWidth() const
    {
        return m_window->GetSize().x;
    }
    u32 Application::GetHeight() const
    {
        return m_window->GetSize().y;
    }
    void Application::OnEvent(Event& event)
    {
        switch(event.type)
        {
            case Event::Closed:
                m_window->Quit();
            break;
            default:
                break;
        }


        for(auto i = m_layerStack.begin(); i != m_layerStack.end(); i++)
            (*i)->OnEvent(event);
    }
    void Application::PushLayer(Layer *layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
        m_layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    void Application::Run()
    {
        while(m_window->IsOpen())
        {
            while(m_window->PeekEvents(m_event))
                OnEvent(m_event);

			Platform::Tick();

            RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.f});
            RendererCommand::Clear();

            ImGuiLayer::OnBegin();



                for(Layer *layer: m_layerStack)
                    layer->OnUpdate();
			
            ImGuiLayer::OnEnd();


            m_context->Renderer();
        }
    }
}
