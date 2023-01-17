
#include <Engine/Core/Input.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Platform.h>
#include <Engine/RHI/DynamicRHI.h>
namespace MeteorEngine
{
	Application* Application::m_ThisInstance = NULL;
	bool	m_HasExitApplication = false;
	DynamicRHI*				GDynamicRHI = NULL;
	RHIShaderCompiler*		GShaderCompilePixelShader = NULL;
	RHIShaderCompiler*		GShaderCompileVertexShader = NULL;
	RHIVertexShader*		GVertexShader = NULL;
	RHIPixelShader*			GPixelShader = NULL;
	RHIVertexLayout* GInputLayout = NULL;
	RHIVertexBuffer* GVertexBuffer = NULL;
	Application::Application()
	{
		m_ThisInstance = this;
		m_Window = std::unique_ptr<Window>(Window::Create("Meteor Engine", Vector2u(1280, 720)));
		GDynamicRHI = DynamicRHI::CreateDynamicRHI();
		GDynamicRHI->Init();
		RHIViewport* viewport = GDynamicRHI->RHICreateViewport(m_Window->GetWindowPtr(), 1280, 720, false);

		GShaderCompilePixelShader = RHIShaderCompiler::StaticCreate();
		GShaderCompilePixelShader->Compile(L"Assets/Shaders/Shader.hlsl", "ps_main", "ps_4_0");		
		
		GShaderCompileVertexShader = RHIShaderCompiler::StaticCreate();
		GShaderCompileVertexShader->Compile(L"Assets/Shaders/Shader.hlsl", "vs_main", "vs_4_0");
		VertexLayoutGroup group({ 
								{ "POS", ShaderElementType::Float3 } 
								});
		GPixelShader	= GDynamicRHI->RHICreatePixelShader(GShaderCompilePixelShader->GetResultCode());
		GVertexShader	= GDynamicRHI->RHICreateVertexShader(GShaderCompileVertexShader->GetResultCode());
		GInputLayout	= GDynamicRHI->RHICreateVertexLayout(GVertexShader, group);
		f32 Vertices[] = {
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f 
		};
		GVertexBuffer = GDynamicRHI->RHICreateVertexBuffer(Vertices, sizeof(Vertices));

	}
	Application::~Application()
	{
		for (auto i = m_LayerStack.begin(); i != m_LayerStack.end(); i++)
			(*i)->OnDetach();

	}
	bool Application::ShouldExit()
	{
		return m_HasExitApplication;
	}
	void Application::Close()
	{
		m_HasExitApplication = true;
		Application::GetInstance().GetWindow().Quit();
	}
	void Application::OnEvent(Event & event)
	{
		if (event.type == Event::Closed)
			Application::Close();
		if (event.type == Event::Resized)
			GDynamicRHI->RHIResizeViewport(Application::GetInstance().GetWidth(), Application::GetInstance().GetHeight(), true);

		for (auto i = m_LayerStack.begin(); i != m_LayerStack.end(); i++)
			(*i)->OnEvent(event);
	}
	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer * overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	void Application::Run()
	{
		while (!ShouldExit())
		{
			Event event;
			while (m_Window->PeekEvents(event))
				OnEvent(event);

			Platform::Tick();
			GDynamicRHI->RHIBegin();
			
			GDynamicRHI->RHIBindVertexLayout(GInputLayout);
			GDynamicRHI->RHIBindVertexBuffer(GVertexBuffer, 12, 0);


			GDynamicRHI->RHIBindVertexShader(GVertexShader);
			GDynamicRHI->RHIBindPixelShader(GPixelShader);


			GDynamicRHI->RHIDrawVertices(3, 0);

			GDynamicRHI->RHIEnd();
		}
	}

}
