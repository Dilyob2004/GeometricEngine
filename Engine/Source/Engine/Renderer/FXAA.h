#ifndef FXAA_H
#define FXAA_H
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Math/Vector2.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/RendererCore/Mesh.h>
namespace GeometricEngine
{
	class GEOMETRIC_API FXAAPass
	{
		struct
		{
			Vector4f rcpFrame;
		}CBFXAA;
	public:
		FXAAPass()
		{

		}
		~FXAAPass()
		{

		}

		void InitPass(const Vector2f& ViewInfo)
		{
			TVector<BufferElement> BufferElements;
			BufferElements.Push({ "POSITION",	ShaderElementType::Float3 });
			BufferElements.Push({ "UV",			ShaderElementType::Float2 });

			RHIPipelineStateDefinition PipelineDefinition;
			PipelineDefinition.VertexParameters = BufferElements;
			PipelineDefinition.PixelShader = GPSResourceMap["PSFXAA"];
			PipelineDefinition.VertexShader = GVSResourceMap["VSFXAA"];
			PipelineDefinition.BlendStateDefinition = RHIBlendStateDefinition();
			PipelineDefinition.DepthStencilStateDefinition = RHIDepthStencilStateDefinition();
			PipelineDefinition.RasterizerStateDefinition = RHIRasterizerStateDefinition();
			FXAAPipeline = GDynamicRHI->RHICreatePipelineState(PipelineDefinition);


			TVector<Vertex2DData> VerticesData;
			VerticesData.Push(Vertex2DData(Vector3f(-1.f, -1.f, 0.0f), Vector2f(0.0f, 1.0f)));
			VerticesData.Push(Vertex2DData(Vector3f(1.f, -1.f, 0.0f), Vector2f(1.0f, 1.0f)));
			VerticesData.Push(Vertex2DData(Vector3f(1.f, 1.f, 0.0f), Vector2f(1.0f, 0.0f)));
			VerticesData.Push(Vertex2DData(Vector3f(-1.f, 1.0f, 0.0f), Vector2f(0.0f, 0.0f)));


			U32 IndicesData[] = { 0, 2, 1, 0, 3, 2 };
			CBFXAA.rcpFrame = Vector4f(1.f / ViewInfo.x, 1.f / ViewInfo.y, 0.f, 0.f);
			VertexBuffer = GDynamicRHI->RHICreateVertexBuffer(VerticesData.Pointer(), sizeof(Vertex2DData) * VerticesData.GetCount(), sizeof(Vertex2DData));
			IndexBuffer = GDynamicRHI->RHICreateIndexBuffer(IndicesData, sizeof(IndicesData));
			UniformBuffer = GDynamicRHI->RHICreateUniformBuffer(&CBFXAA, sizeof(CBFXAA));


			SamplerState = GDynamicRHI->RHICreateSamplerState(RHISamplerStateDefinition());
		}

		void AddPass(RHITexture2D* InRenderTarget, RHITexture2D* OutRenderTarget, const Vector2f& ViewInfo)
		{
			CBFXAA.rcpFrame = Vector4f(1.f / ViewInfo.x, 1.f / ViewInfo.y, 0.f, 0.f);
			GDynamicRHI->RHISetRenderTarget(OutRenderTarget);
			GDynamicRHI->RHISetPipelineState(FXAAPipeline);

			GDynamicRHI->RHISetSamplerState(GPSResourceMap["PSFXAA"], SamplerState);
			GDynamicRHI->RHISetTexture(GPSResourceMap["PSFXAA"], InRenderTarget);

			GDynamicRHI->RHIUpdateUniformBuffer(UniformBuffer, &CBFXAA, sizeof(CBFXAA));
			GDynamicRHI->RHISetUniformBuffer(GPSResourceMap["PSFXAA"], UniformBuffer);

			GDynamicRHI->RHIDrawPrimitiveIndexed(VertexBuffer, IndexBuffer, 6, 0);
		}
	private:

		RHIVertexBuffer* VertexBuffer;
		RHIIndexBuffer* IndexBuffer;
		RHIUniformBuffer* UniformBuffer;
		RHIPipelineState* FXAAPipeline;
		RHISamplerState* SamplerState;
	};
}
#endif // !FXAA_H
