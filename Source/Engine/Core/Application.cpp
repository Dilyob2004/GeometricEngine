
#include <Engine/Core/Input.h>
#include <Engine/Gui/ImGuiLayer.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/RenderContext.h>
//#include <Editor/ExampleLayer.h>
#include <Engine/Render/Camera.h>
#include <Engine/Render/VertexBuffer.h>
#include <Engine/Render/IndexBuffer.h>
#include <Engine/Render/Shader.h>
#include <Engine/Render/RenderPass.h>
#include <Editor/Editor.h>
#include <Engine/Math/MathUtils.h>
#include <limits>
#include <fstream>
namespace MeteorEngine
{
	bool	m_HasExitApplication = false;
    Application* Application::m_ThisInstance = NULL;
	Camera m_Camera;
	VertexBuffer* m_SquareBuffer = NULL;
	IndexBuffer* m_IndexBuffer = NULL;
	Shader* m_Shader = NULL;
	Pipeline* pipeLine = NULL;
	RenderPass* renderPass = NULL;
	FrameBuffer* frameBuffer[3];
	DescriptorSet* descriptorSet = NULL;
	std::vector<DescriptorSet*> m_DescriptorSet;
	f32 vertices[] = {
		0.0f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	u32 indices[] = { 0, 1, 2, 2, 1, 0 };
    Application::Application()
    {
		m_ThisInstance = this;
		//ImGuiLayer::OnEnableHighDpi();
		m_Window = std::unique_ptr<Window>( Window::Create("Meteor Engine", Vector2u(1280, 720) ) );
		InitPlatformVulkan();
		// Our state
		RenderContext* Context = RenderContext::Create(m_Window.get());
		RendererCommand::Init(Context, m_Window.get()->GetSize(), true);
		m_Camera = Camera(30, 1.778f, 0.1f, 1000);
		//PushLayer(new ImGuiLayer());

		m_SquareBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		m_Shader = Shader::Create("Assets/Shaders/quad.vert.spv", "Assets/Shaders/quad.frag.spv");
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(u32));
		DescriptorInfo info;
		info.count = 1;
		info.layoutIndex = 0;
		info.shader = m_Shader;
		descriptorSet = DescriptorSet::Create(info);
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


        for(auto i = m_LayerStack.begin(); i != m_LayerStack.end(); i++)
            (*i)->OnEvent(event);
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
		PipelineInfo info;
		info.SwapChainTarget = true;
		info.PipelineShader = m_Shader;
		pipeLine = Pipeline::Create(info);
        while(!ShouldExit())
        {
			Event event;
            while(m_Window->PeekEvents(event))
                OnEvent(event);

			Platform::Tick();

			RendererCommand::Begin();

			auto cmd = RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer();
			auto index = RendererCommand::GetMainSwapChain()->GetCurrentImageIndex();
			pipeLine->ClearRenderTargets(cmd);
			pipeLine->Begin(cmd);
			Matrix4f transform = Translate(Matrix4f::Identity, Vector3f(0, 0, 0));
			Matrix4f viewProj = m_Camera.GetViewProjection();
			descriptorSet->SetUniform("Quad", "u_Transform", &transform);
			descriptorSet->SetUniform("Quad", "u_ViewProjection", &viewProj);
			descriptorSet->Update();


			RendererCommand::BindDescriptorSets(pipeLine, cmd, 0, &descriptorSet, 1);
			RendererCommand::DrawIndexed(cmd, DrawType::TRIANGLE, 6, 0);
			/*
				ImGuiLayer::OnBegin();
					for (auto i = m_LayerStack.begin(); i != m_LayerStack.end(); i++)
						(*i)->OnTick();
				ImGuiLayer::OnEnd();*/
			pipeLine->End(cmd);

			RendererCommand::Present();

        }
    }
}
