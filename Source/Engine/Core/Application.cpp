
#include <Engine/Core/Input.h>
#include <Engine/Gui/ImGuiLayer.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <Editor/ExampleLayer.h>
#include <Editor/Editor.h>
namespace MeteorEngine
{


	LayerStack layerStack;
	bool isExitApplication = false;
    Application* Application::m_instance = NULL;

    Application::Application()
    {
		m_instance = this;
		//ImGuiLayer::OnEnableHighDpi();
        m_window    = std::unique_ptr<Window>( Window::Create("Meteor Engine, OpenGL Build 4.3.0", Vector2u(1280, 720) ) );
       // m_context   = std::unique_ptr<RenderContext>(RenderContext::Create(m_window.get()));

		InitPlatformVulkan();
		VulkanContext* context = new VulkanContext();
       // m_context->SetVSync(true);
		///Initizlize 
		//RendererCommand::InitEngine();

        //PushLayer(new ImGuiLayer());
        //PushLayer(new Editor());
        //PushLayer(new ExampleLayer());
    }
    Application::~Application()
    {
        for(auto i = layerStack.begin(); i != layerStack.end(); i++)
            (*i)->OnDetach();

    }
	bool Application::ShouldExit()
	{
		return isExitApplication;
	}
	void Application::Exit()
	{
		isExitApplication = true;
		exit(0);
	}
    void Application::OnEvent(Event& event)
    {
		switch (event.type)
		{
		case Event::Closed:
			Exit();
			m_window->Quit();
			break;

			
		}


        for(auto i = layerStack.begin(); i != layerStack.end(); i++)
            (*i)->OnEvent(event);
    }
    void Application::PushLayer(Layer *layer)
    {
		layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
		layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    void Application::Run()
    {
        while(!ShouldExit())
        {
			Event event;
            while(m_window->PeekEvents(event))
                OnEvent(event);

			Platform::Tick();
            /**ImGuiLayer::OnBegin();
                for(Layer *layer: layerStack)
                    layer->OnTick();
            ImGuiLayer::OnEnd();


            m_context->Renderer();*/
        }
    }
}
