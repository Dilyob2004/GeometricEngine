
#include <Engine/Core/Input.h>
#include <Engine/Gui/ImGuiLayer.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Platform/Win32/VulkanSupport.h>
#include <Engine/Render/ImageCore.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <Editor/ExampleLayer.h>
#include <Editor/Editor.h>
#include <limits>

namespace MeteorEngine
{

	LayerStack layerStack;
	bool isExitApplication = false;
    Application* Application::m_instance = NULL;
	VulkanContext* vkContext;
    Application::Application()
    {
		m_instance = this;
		//ImGuiLayer::OnEnableHighDpi();
        m_window    = std::unique_ptr<Window>( Window::Create("Meteor Engine", Vector2u(1280, 720) ) );
        //m_context   = std::unique_ptr<RenderContext>(RenderContext::Create(m_window.get()));

		InitPlatformVulkan();
		//vkApi = new VulkanExample(m_window.get());
		vkContext = new VulkanContext();

		vkContext->Create(m_window.get());
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
	void Application::Close()
	{
		isExitApplication = true;
	}
    void Application::OnEvent(Event& event)
    {
		switch (event.type)
		{
			case Event::Closed:
					Application::Close();
					m_window->Quit();
				break;
		}


       // for(auto i = layerStack.begin(); i != layerStack.end(); i++)
           // (*i)->OnEvent(event);
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
            ImGuiLayer::OnEnd();*/
			//vkApi->draw();
			
			vkContext->Present();
			Sleep(1);
        }
    }
}
