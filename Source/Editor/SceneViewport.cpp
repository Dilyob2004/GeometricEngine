#include "SceneViewport.h"

#include <Engine/ImageCore/ImageCore.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/RendererCore/ShaderResource.h>
#include <Engine/RendererCore/TextureResource2D.h>
#include <ImGui/imgui.h>

namespace GeometricEngine
{
	static RHIConstantBuffer* GConstantBuffer;
	static RHIVertexBuffer* GVertexBuffer;
	static RHIIndexBuffer* GIndexBuffer;

	TSharedPtr<BoundShaderResource> ShaderCache;
	TSharedPtr<TextureResource2D> TextureCache;
	struct
	{
		Matrix4f ViewProjection;
	}CBuffer;


	SceneViewport::SceneViewport()
	{
		InitRenderTarget();
		{

			BlendState.reset(GDynamicRHI->RHICreateBlendState(RHIBlendStateDefinition()));
			RasterizerState.reset(GDynamicRHI->RHICreateRasterizerState(RHIRasterizerStateDefinition()));
			DepthStencilState.reset(GDynamicRHI->RHICreateDepthStencilState(RHIDepthStencilStateDefinition()));
		}


		struct
		{
			Vector3f Position;
			Vector2f UV;
		}Vertices[4];






		TVector<BufferElement> BufferElements;
		BufferElements.Push({ "POSITION" , ShaderElementType::Float3 });
		BufferElements.Push({ "UV" , ShaderElementType::Float2 });

		ShaderCache.reset(new BoundShaderResource(BufferElements, 
													GVSResourceMap["ScreenVSTexture"], 
													GPSResourceMap["ScreenPSTexture"]));
		Vertices[0].Position	= Vector3f(-0.5f, -0.5f, 0.0f);
		Vertices[0].UV			= Vector2f(0.0f, 1.0f);

		Vertices[1].Position	= Vector3f(0.5f, -0.5f, 0.0f);
		Vertices[1].UV			= Vector2f(1.0f, 1.0f);

		Vertices[2].Position	= Vector3f(0.5f, 0.5f, 0.0f);
		Vertices[2].UV			= Vector2f(1.0f, 0.0f);

		Vertices[3].Position	= Vector3f(-0.5f, 0.5f, 0.0f);
		Vertices[3].UV			= Vector2f(0.0f, 0.0f);

		U32 Indices[] = { 0, 2, 1, 0, 3, 2 };
		SceneCamera.SetProjection(45 * MATH_RADIANS, 0.01f, 1000.f);
		CBuffer.ViewProjection = SceneCamera.GetViewProjection();

		GVertexBuffer = GDynamicRHI->RHICreateVertexBuffer(Vertices, sizeof(Vertices));
		GIndexBuffer = GDynamicRHI->RHICreateIndexBuffer(Indices, sizeof(Indices));

		GConstantBuffer = GDynamicRHI->RHICreateConstantBuffer(&CBuffer, sizeof(CBuffer));


		Image Resource;

		if (Resource.Load("../../Content/Logo/512x512.png"))
		{
			RHITextureDefinition Def;
			Def.Width = Resource.GetWidth();
			Def.Height = Resource.GetHeight();
			Def.Data = Resource.GetRawData();
			Def.Flags = TF_ShaderResource;
			Def.Format = RHIPixelFormat::R8G8BA8_UNORM;
			Def.MipLevels = 1;
			Def.Samples = 1;
			TextureCache.reset(new TextureResource2D(Def, RHISamplerStateDefinition(), ShaderCache.get()));
		}


	}
	SceneViewport::~SceneViewport()
	{
	}


	void SceneViewport::InitRenderTarget()
	{
		if (RenderTarget) RenderTarget->SafeRelease();
		if (DepthTarget) DepthTarget->SafeRelease();

		///RenderTarget
		{
			RHITextureDefinition Definition;
			Definition.Flags = TF_RenderTarget | TF_ShaderResource;
			Definition.Format = RHIPixelFormat::R8G8BA8_UNORM;
			Definition.Width = (U32)SceneViewSize.x;
			Definition.Height = (U32)SceneViewSize.y;
			RenderTarget = (GDynamicRHI->RHICreateTexture2D(Definition));
		}
		///DepthTarget
		{
			RHITextureDefinition Definition;
			Definition.Flags = TF_DepthStencil;
			Definition.Width = (U32)SceneViewSize.x;
			Definition.Height = (U32)SceneViewSize.y;
			Definition.Format = RHIPixelFormat::DEPTH32_F32;
			DepthTarget = (GDynamicRHI->RHICreateTexture2D(Definition));
		}
	}
	void SceneViewport::OnDrawRenderer()
	{
		SceneCamera.OnTick(0.5f);


		GDynamicRHI->RHIClearRenderTarget(RenderTarget, 30, 30, 30, 30);
		GDynamicRHI->RHIClearDepthTarget(DepthTarget, true, true, 1.0f);
		GDynamicRHI->RHISetRenderTarget(RenderTarget, DepthTarget);

		GDynamicRHI->RHISetDepthStencilState(DepthStencilState.get());
		GDynamicRHI->RHISetBlendState(BlendState.get());
		GDynamicRHI->RHISetRasterizerState(RasterizerState.get());


		GDynamicRHI->RHISetVertexBuffer(GVertexBuffer, ShaderCache->GetVertexLayout());
		GDynamicRHI->RHISetIndexBuffer(GIndexBuffer);

		CBuffer.ViewProjection = SceneCamera.GetViewProjection();
		GDynamicRHI->RHISetConstantBuffer(ShaderCache->GetVertexShader(), GConstantBuffer);
		GDynamicRHI->RHIUpdateConstantBuffer(GConstantBuffer, &CBuffer, sizeof(CBuffer));
		TextureCache->OnTick();

		GDynamicRHI->RHIDrawPrimitiveIndexed(6, 0);
	}
	void SceneViewport::OnDrawSceneViewport()
	{



		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0 ,0 });
			ImGui::Begin("Viewport");
				ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
				if (SceneViewSize.x != ViewportPanelSize.x || SceneViewSize.y != ViewportPanelSize.y)
				{
					SceneViewSize.x = ViewportPanelSize.x;
					SceneViewSize.y = ViewportPanelSize.y;

					InitRenderTarget();

					SceneCamera.OnResize(SceneViewSize);
				}
				ImGui::Image(RenderTarget->GetHandle(), {SceneViewSize.x, SceneViewSize.y});

			ImGui::End();
		ImGui::PopStyleVar();
	}
}