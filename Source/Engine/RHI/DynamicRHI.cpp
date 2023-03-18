#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/RHIModule.h>
#include <Engine/Core/Application.h>
#include <Engine/ShaderCompiler/ShaderCompiler.h>
namespace GeometricEngine
{
	DynamicRHI* GDynamicRHI = NULL;
	RHIViewport* GMainViewport = NULL;

	RHIModule::RHIModule() : EngineModule("RHIModule")
	{
	}
	RHIModule::~RHIModule() { }

	RHIVertexShader*	GVertexShader;
	RHIVertexLayout* GVertexLayout;
	RHIPixelShader*		GPixelShader;
	RHIVertexBuffer*	GVertexBuffer;
	RHIIndexBuffer*		GIndexBuffer;
	bool RHIModule::Initialize()
	{
		GDynamicRHI = DynamicRHI::CreateDynamicRHI();
		if (!GDynamicRHI->Initialize()) 
		{
			return false;
		}

		GMainViewport = GDynamicRHI->RHICreateViewport(	Application::GetMainWindow()->GetHandle(),
														Application::GetMainWindow()->GetWidth(),
														Application::GetMainWindow()->GetHeight(),
														false);

		ShaderCompilerInput Input;
		ShaderCompilerOutput Output;
		Input.Type = ShaderType::Vertex;
		Input.Model = ShaderModel::SM5;
		Input.ShaderName = "Shader.hlsl";
		Input.EntryPoint = "VSMain";
		CompileShader(Input, Output);


		GVertexShader = GDynamicRHI->RHICreateVertexShader(Output.Code);

		TVector<BufferElement> BufferElements;
		BufferElements.Push({ "POSITION" , ShaderElementType::Float3 });
		BufferElements.Push({ "COLOR" , ShaderElementType::Float3 });
		GVertexLayout = GDynamicRHI->RHICreateVertexLayout(GVertexShader, BufferElements);


		Input.Type = ShaderType::Pixel;
		Input.Model = ShaderModel::SM5;
		Input.ShaderName = "Shader.hlsl";
		Input.EntryPoint = "PSMain";
		CompileShader(Input, Output);

		GPixelShader = GDynamicRHI->RHICreatePixelShader(Output.Code);
		F32 Vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.f, 1.f, 1.f,
			 0.5f, -0.5f, 0.0f, 1.f, 1.f, 1.f,
			 0.5f,  0.5f, 0.0f, 1.f, 1.f, 1.f,
			-0.5f,  0.5f, 0.0f, 1.f, 1.f, 1.f,
		};
		U32 Indices[] = { 0, 2, 1, 0, 3, 2 };
		GVertexBuffer = GDynamicRHI->RHICreateVertexBuffer(Vertices, sizeof(Vertices));
		GIndexBuffer = GDynamicRHI->RHICreateIndexBuffer(Indices, sizeof(Indices));

		return true;
	}
	void RHIModule::Tick()
	{
		GDynamicRHI->RHIBegin(GMainViewport);


		GDynamicRHI->RHIBindVertexLayout(GVertexLayout);
		GDynamicRHI->RHIBindVertexBuffer(GVertexBuffer, GVertexLayout);
		GDynamicRHI->RHIBindIndexBuffer(GIndexBuffer);
		GDynamicRHI->RHIBindVertexShader(GVertexShader);
		GDynamicRHI->RHIBindPixelShader(GPixelShader);

		

	}
	void RHIModule::Draw()
	{
		GDynamicRHI->RHIDraw(6, 0);
		GDynamicRHI->RHIEnd(GMainViewport);
	}
	void RHIModule::DeInitialize()
	{
	}
}