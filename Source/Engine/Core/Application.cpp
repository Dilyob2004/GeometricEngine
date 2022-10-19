
#include <Engine/Core/Input.h>
#include <Engine/Gui/ImGuiLayer.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Platform/Win32/VulkanSupport.h>
#include <Engine/Render/RenderContext.h>
#include <Editor/ExampleLayer.h>
#include <Editor/Editor.h>
#include <limits>

namespace MeteorEngine
{

	bool	m_HasExitApplication = false;
    Application* Application::m_ThisInstance = NULL;
    Application::Application()
    {
		m_ThisInstance = this;
		//ImGuiLayer::OnEnableHighDpi();
		m_Window = std::unique_ptr<Window>( Window::Create("Meteor Engine", Vector2u(1280, 720) ) );

		InitPlatformVulkan();

		m_Context = std::unique_ptr<RenderContext>(RenderContext::Create(m_Window.get()));
		RendererCommand::Init(m_Context.get(), m_Window->GetSize(), true);
    }
    Application::~Application()
    {
        for(auto i = m_LayerStack.begin(); i != m_LayerStack.end(); i++)
            (*i)->OnDetach();

    }
	bool Application::ShouldExit()
	{
		return m_HasExitApplication;
	}
	void Application::Close()
	{
		m_HasExitApplication = true;
	}
    void Application::OnEvent(Event& event)
    {
		switch (event.type)
		{
			case Event::Closed:
					Application::Close();
					m_Window->Quit();
				break;

			case Event::Resized:
				RendererCommand::Resize({ event.size.width, event.size.height });
				break;
		}


       // for(auto i = layerStack.begin(); i != layerStack.end(); i++)
           // (*i)->OnEvent(event);
    }
    void Application::PushLayer(Layer *layer)
    {
		m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
		m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    void Application::Run()
    {
        while(!ShouldExit())
        {
			Event event;
            while(m_Window->PeekEvents(event))
                OnEvent(event);

			Platform::Tick();
			RendererCommand::Begin();
            /**ImGuiLayer::OnBegin();
                for(Layer *layer: layerStack)
                    layer->OnTick();
            ImGuiLayer::OnEnd();*/
			RendererCommand::Present();
        }
    }
}
