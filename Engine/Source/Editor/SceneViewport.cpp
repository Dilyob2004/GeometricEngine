#include "SceneViewport.h"

#include <Engine/ImageCore/ImageCore.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/RendererCore/ShaderResource.h>
#include <Engine/InputCore/InputCore.h>
#include <Engine/RendererCore/Mesh.h>
#include <Engine/Renderer/FXAA.h>
#include <ImGui/imgui.h>
namespace GeometricEngine
{

	TSharedPtr<Mesh> MeshCache;
	RHIPipelineState* Pipeline;
	RHITexture2D* RenderTargetFXAA;

	FXAAPass Pass;
	SceneViewport::SceneViewport()
	{
		InitRenderTarget();
		{
			TVector<BufferElement> BufferElements;
			BufferElements.Push({ "POSITION",	ShaderElementType::Float3 });
			BufferElements.Push({ "NORMAL",			ShaderElementType::Float3 });

			RHIPipelineStateDefinition PipelineDefinition;
			PipelineDefinition.VertexParameters = BufferElements;
			PipelineDefinition.PixelShader = GPSResourceMap["ScreenPixelShader"];
			PipelineDefinition.VertexShader = GVSResourceMap["ScreenVertexShader"];
			PipelineDefinition.BlendStateDefinition = RHIBlendStateDefinition();
			PipelineDefinition.DepthStencilStateDefinition = RHIDepthStencilStateDefinition();
			PipelineDefinition.RasterizerStateDefinition = RHIRasterizerStateDefinition();
			Pipeline = GDynamicRHI->RHICreatePipelineState(PipelineDefinition);
			MeshCache.reset(MakeCube());
		}
		
		SceneCamera.SetProjection(45 * MATH_RADIANS, 0.01f, 1000.f);
		Pass.InitPass(SceneViewSize);

		/*Image Resource;

		if (Resource.Load("../../Content/Logo/512x512.png"))
		{
			RHITextureDefinition Def;
			Def.Width = Resource.GetWidth();
			Def.Height = Resource.GetHeight();
			Def.Data = Resource.GetRawData();
			Def.Format = RHIPixelFormat::R8G8BA8_UNORM;
			Def.Flags = TF_ShaderResource;
			TextureCache.reset(new TextureResource2D(Def, RHISamplerStateDefinition()));
		}
		*/

	}
	SceneViewport::~SceneViewport()
	{
	}


	void SceneViewport::InitRenderTarget()
	{
		if (RenderTarget) RenderTarget->SafeRelease();
		if (RenderTargetFXAA) RenderTargetFXAA->SafeRelease();
		if (DepthTarget) DepthTarget->SafeRelease();

		///RenderTarget
		{
			RHITextureDefinition Definition;
			Definition.Flags = TF_RenderTarget | TF_ShaderResource;
			Definition.Format = RHIPixelFormat::R8G8BA8_UNORM;
			Definition.Width = (U32)SceneViewSize.x;
			Definition.Height = (U32)SceneViewSize.y;
			Definition.Samples = 1;
			RenderTarget = (GDynamicRHI->RHICreateTexture2D(Definition));
		}
		///RenderTarget
		 {
			RHITextureDefinition Definition;
			Definition.Flags = TF_RenderTarget | TF_ShaderResource;
			Definition.Format = RHIPixelFormat::R8G8BA8_UNORM;
			Definition.Width = (U32)SceneViewSize.x;
			Definition.Height = (U32)SceneViewSize.y;
			Definition.Samples = 1;
			RenderTargetFXAA = (GDynamicRHI->RHICreateTexture2D(Definition));
		}
		///DepthTarget
		{
			RHITextureDefinition Definition;
			Definition.Flags = TF_DepthStencil;
			Definition.Width = (U32)SceneViewSize.x;
			Definition.Height = (U32)SceneViewSize.y;
			Definition.Format = RHIPixelFormat::DEPTH32_F32;
			Definition.Samples = 1;
			DepthTarget = (GDynamicRHI->RHICreateTexture2D(Definition));
		}
	}
	void SceneViewport::OnTick()	
	{
		SceneCamera.OnTick(0.5f);
		
	}
	void SceneViewport::OnDrawRenderer()
	{

		GDynamicRHI->RHISetRenderTarget(RenderTarget, DepthTarget);
		GDynamicRHI->RHIClearRenderTarget(RenderTarget, 30, 30, 30, 30);
		GDynamicRHI->RHIClearDepthTarget(DepthTarget, true, true, 1.0f);
		GDynamicRHI->RHISetPipelineState(Pipeline);
			MeshCache->OnTick(GVSResourceMap["ScreenVertexShader"], SceneCamera.GetViewProjection());
		

			Pass.AddPass(RenderTarget, RenderTargetFXAA, SceneViewSize);
			//GDynamicRHI->RHICopyRenderTarget(RenderTargetFXAA, RenderTarget);


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
			ImGui::Image(RenderTargetFXAA->GetHandle(), { SceneViewSize.x, SceneViewSize.y });

		ImGui::End();
		ImGui::PopStyleVar();


	}
}