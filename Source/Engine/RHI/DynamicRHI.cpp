#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/RHIModule.h>
#include <Engine/Core/Application.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/RendererCore/ViewportClient.h>
#include <Engine/Math/MathUtils.h>
#include <Engine/ImageCore/ImageCore.h>
namespace GeometricEngine
{
	DynamicRHI* GDynamicRHI = NULL;
	ViewportClient* GClient = NULL;
	RHIModule::RHIModule() : EngineModule("RHIModule")
	{
	}
	RHIModule::~RHIModule() { }

	RHIVertexShader*	GVertexShader;
	RHIVertexLayout*	GVertexLayout;
	RHIConstantBuffer*  GConstantBuffer;
	RHIPixelShader*		GPixelShader;
	RHIPixelShader*		GFXAAShader;
	RHIVertexBuffer*	GVertexBuffer;
	RHIIndexBuffer*		GIndexBuffer;
	RHIBlendState*		GBlendState;
	RHIRasterizerState* GRasterizerState;
	RHIDepthStencilState* GDepthStencilState;
	class CameraOrtho
	{
	public:
		CameraOrtho(float AsepctRatio) :
			View(1)
			, WorldPosition(0, 0, 0)
			, WorldRotation(0)
		{
			SetProjection(-AsepctRatio, AsepctRatio, -1, 1);
		}

		void SetProjection(F32 Left, F32 Right, F32 Bottom, F32 Top)
		{
			Matrix4f transform = Translate(Matrix4f::Identity, WorldPosition) *
								 Rotate(Matrix4f::Identity, WorldRotation, {0, 0, 1.f});

			View = Inverse(transform);
			Projection = Ortho(Left, Right, Bottom, Top);
			ViewProjection = Projection * View;
		}
		void SetPosition(const Vector3f& Position)
		{
			WorldPosition = Position;
			Matrix4f transform = Translate(Matrix4f::Identity, WorldPosition) *
				Rotate(Matrix4f::Identity, WorldRotation, { 0, 0, 1.f });

			View = Inverse(transform);
			ViewProjection = Projection * View;
		}
		Matrix4f GetViewProjection() const { return ViewProjection; }
	private:

	private:
		Matrix4f View, Projection, ViewProjection;

		Vector3f WorldPosition;
		F32 WorldRotation;
	};
	Matrix4f View;

	RHITexture2D* Texture;
	RHISamplerState* Sampler;

	bool RHIModule::Initialize()
	{
		GDynamicRHI = DynamicRHI::CreateDynamicRHI();
		GClient = new ViewportClient();
		if (!GDynamicRHI->Initialize()) 
			return false;

		GClient->Initialize();
		ShaderCompilerWorker::Initialize();




		GVertexShader = GDynamicRHI->RHICreateVertexShader(GShadersMap["ScreenVSTexture"].Code);
		GPixelShader = GDynamicRHI->RHICreatePixelShader(GShadersMap["ScreenPSTexture"].Code);

		TVector<BufferElement> BufferElements;
		BufferElements.Push({ "POSITION" , ShaderElementType::Float3 });
		BufferElements.Push({ "UV" , ShaderElementType::Float2 });
		GVertexLayout = GDynamicRHI->RHICreateVertexLayout(GVertexShader, BufferElements);




		F32 Vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.f, 1.f,
			 0.5f, -0.5f, 0.0f, 1.f, 1.f,
			 0.5f,  0.5f, 0.0f, 1.f, 0.f,
			-0.5f,  0.5f, 0.0f, 0.f, 0.f
		};
		U32 Indices[] = { 0, 2, 1, 0, 3, 2 };	
		CameraOrtho Camera2D((F32)Application::GetMainWindow()->GetWidth() / (F32)Application::GetMainWindow()->GetHeight());
		View = Camera2D.GetViewProjection();
		GVertexBuffer = GDynamicRHI->RHICreateVertexBuffer(Vertices, sizeof(Vertices));
		GIndexBuffer = GDynamicRHI->RHICreateIndexBuffer(Indices, sizeof(Indices));
		GConstantBuffer = GDynamicRHI->RHICreateConstantBuffer(&View[0], sizeof(View));


		Image Resource;
		if (Resource.Load("../../Content/Logo/512x512.png"))
		{
			RHITextureDefinitions Def;
			Def.Width		= Resource.GetWidth();
			Def.Height		= Resource.GetHeight();
			Def.Data		= Resource.GetRawData();
			Def.Flags		= TF_ShaderResource;
			Def.Format		= RHIPixelFormat::R8G8BA8_UNORM;
			Def.MipLevels	= 1;
			Def.Samples		= 1;
			Texture = GDynamicRHI->RHICreateTexture2D(Def);
		}
		Sampler				= GDynamicRHI->RHICreateSamplerState(RHISamplerStateDefinition());
		GBlendState			= GDynamicRHI->RHICreateBlendState(RHIBlendStateDefinition());
		GRasterizerState	= GDynamicRHI->RHICreateRasterizerState(RHIRasterizerStateDefinition());
		GDepthStencilState	= GDynamicRHI->RHICreateDepthStencilState(RHIDepthStencilStateDefinition());
		return true;
	}
	void RHIModule::Tick()
	{

		GClient->BeginFrame();
		GDynamicRHI->RHISetVertexLayout(GVertexLayout);
		GDynamicRHI->RHISetVertexBuffer(GVertexBuffer, GVertexLayout);
		GDynamicRHI->RHISetIndexBuffer(GIndexBuffer);
		GDynamicRHI->RHISetVertexShader(GVertexShader);
		GDynamicRHI->RHISetPixelShader(GPixelShader);

		GDynamicRHI->RHISetConstantBuffer(GVertexShader, GConstantBuffer);
		GDynamicRHI->RHIUpdateConstantBuffer(GConstantBuffer, &View[0], sizeof(View));

		GDynamicRHI->RHISetTexture(GPixelShader,  Texture);
		GDynamicRHI->RHISetSamplerState(GPixelShader, Sampler);
		GDynamicRHI->RHISetDepthStencilState(GDepthStencilState);
		GDynamicRHI->RHISetBlendState(GBlendState);
		GDynamicRHI->RHISetRasterizerState(GRasterizerState);
	}
	void RHIModule::Draw()
	{
		GDynamicRHI->RHIDrawPrimitiveIndexed(6, 0);
		GClient->EndFrame();
	}
	void RHIModule::DeInitialize()
	{
	}
}